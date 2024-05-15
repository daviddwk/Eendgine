#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <eendgine/model.hpp>
#include <eendgine/collisionGeometry.hpp>
#include <eendgine/screen.hpp>
#include <eendgine/renderBatch.hpp>

#include <stb/stb_image.h>
//#include "player.hpp"

#include <iostream>
#include <vector>
#include <numbers>

namespace Eend = Eendgine;

const unsigned int screenHeight = 750;
const unsigned int screenWidth = 1000; 

int main(){
    Eend::Window::init(screenWidth, screenHeight, "Quack"); 
    Eend::Screen::init(screenWidth, screenHeight);
    Eend::FrameLimiter::setFPS(30.0f);
    
    glEnable(GL_DEPTH_TEST);

    Eend::TextureCache myTextureCache;
    
    Eend::ShaderProgram myShader("shaders/shader.vert", "shaders/shader.frag");
    Eend::ShaderProgram myShader3D("shaders/shader3D.vert", "shaders/shader3D.frag");
    Eend::ShaderProgram myInpolShader("shaders/shaderInpol.vert", "shaders/shaderInpol.frag");
    Eend::ShaderProgram screenShader("shaders/shaderScreen.vert", "shaders/shaderScreen.frag");

    Eend::Camera3D my3DCamera((float)screenWidth / (float)screenHeight,
            glm::vec3(20.0f, 15.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
    Eend::Camera2D myCamera(screenWidth, screenHeight);

    
    Eend::Sprite mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    mySprite.setPosition(300.0f, 300.0f);
    mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    my3DSprite.setPosition(20.0f, 0.0f, 0.0f);
    my3DSprite.setSize(10.0f, 10.0f);

    glm::vec3 mp = glm::vec3(0.0f, 50.0f, 0.0f);

    Eend::StaticModel myModel("resources/ost/ost.obj", myTextureCache);
    myModel.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    myModel.setPosition(glm::vec3(mp.x, mp.y + 4, mp.z));
    Eend::CollisionCylinder myCylinder(glm::vec3(mp.x, mp.y, mp.z), 1.0f, 3.0f);
    
    std::vector<std::string> courtAnim;
    for (int i = 1; i <= 4; i++) {
        courtAnim.emplace_back("resources/court/court" + std::to_string(i) + ".obj");
    }

    myModel.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    myModel.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    Eend::AnimatedModel myAnimatedCourt(courtAnim, myTextureCache);
    myAnimatedCourt.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    myAnimatedCourt.setScale(glm::vec3(4.0f));
    myAnimatedCourt.setAnim(0.0f);
    Eend::CollisionModel myColCourt("resources/courtCol/courtHitbox.obj");
    myColCourt.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    myColCourt.setScale(glm::vec3(4.0f));
    
    
    std::vector<Eend::CollisionModel*> myColModels = {
            &myColCourt};


    std::vector<Eend::Model*> modelBatch;
    modelBatch.push_back(&myModel);
    
    float fv = 0.0f;
    float camPosX = 0;
    float camPosY = 0;
    
    while(!Eend::InputManager::shouldClose){
        Eend::FrameLimiter::startInterval(); 
        Eend::Screen::bind();
        screenShader.setInt("pixelSize", 5);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // drawing 3D
        //myCube.draw(myShader3D, my3DCamera, true);
        //myModel.draw(myShader3D, my3DCamera, true);
        renderModelBatch(&modelBatch, myShader3D, my3DCamera);
        my3DSprite.draw(myShader3D, my3DCamera);

        myAnimatedCourt.draw(myInpolShader, my3DCamera, true);

        glClear(GL_DEPTH_BUFFER_BIT);
        // drawing HUD
        mySprite.draw(myShader, myCamera);
        
        float dt = Eend::FrameLimiter::deltaTime / 4;
        if (dt > 1.0f / 60.0f) dt = 1.0f / 60.0f;

        for(int i = 0; i < 4; i++) {
            float speed = 20.000f;
            // move based on input and gravity
            camPosX += Eend::InputManager::deltaMouseX / 100.0f;
            camPosY += Eend::InputManager::deltaMouseY / 100.0f;

            // so that this number doesn't grow out of control and lose accuracy it loops at 2pi
            while (camPosX > std::numbers::pi) {
                camPosX -= 2 * std::numbers::pi;
            }
            while (camPosX < std::numbers::pi) {
                camPosX += 2 * std::numbers::pi;
            }

            // capping the camera height at the top of the sin wave
            if (camPosY > std::numbers::pi * 0.5) {
                camPosY = std::numbers::pi * 0.5;
            } else if (camPosY < -(std::numbers::pi * 0.5)) {
                camPosY = -(std::numbers::pi * 0.5);
            }
            
            if (fv > -50.0f) {
                fv -= 1.0f;
            }
            
            if (Eendgine::InputManager::upPress) {
                // TODO fix adjustment and find out where forward actually is
                myModel.setRadians(camPosX + (std::numbers::pi / 2), 0.0f);
                mp.x -= (speed * cos(camPosX)) * dt;
                mp.z -= (speed * sin(camPosX)) * dt;
            }
            if (Eendgine::InputManager::downPress) {
                mp.x += (speed * cos(camPosX)) * dt;
                mp.z += (speed * sin(camPosX)) * dt;
            }
            if (Eendgine::InputManager::leftPress) {
                mp.x -= (speed * sin(camPosX)) * dt;
                mp.z += (speed * cos(camPosX)) * dt;
            }
            if (Eendgine::InputManager::rightPress) {
                mp.x += (speed * sin(camPosX)) * dt;
                mp.z -= (speed * cos(camPosX)) * dt;
            }
            if (Eendgine::InputManager::spacePress) {
                fv = 25;
            }
            
            mp.y += fv * dt;
            // adjust for collisions
            //
            myCylinder.setPosition(glm::vec3(mp.x, mp.y, mp.z));
            bool hitWall = false;
            bool hitCeiling = false;
            bool hitFloor = false;
            Eend::CollisionResults colResults = Eend::adjustToCollision(myCylinder, myColModels);
            if (auto floorHeight = colResults.floor) {
                std::cout << "FLOOR\n" << std::endl;
                mp.y = *floorHeight;
                if(fv < 0) fv = 0;
            } else if (auto ceilingHeight = colResults.ceiling) {
                std::cout << "CEILING\n" << std::endl;
                mp.y = *ceilingHeight;
                if(fv > 0) fv = 0;
            } else {
                std::cout << "NEITHER\n" << std::endl;
            }
            if (auto wallOffset = colResults.wall) {
                mp.x = wallOffset->x;
                mp.z = wallOffset->z;
            }
            myCylinder.setPosition(glm::vec3(mp.x, mp.y, mp.z));

            mp = myCylinder.getPosition();
            myModel.setPosition(glm::vec3(mp.x, mp.y + 4, mp.z));
            /*
            float height = 0;
            if (Eend::pushCylinderFromCeiling(myCylinder, myColCeil, &height)) {
                if (fv > 0) fv = 0;
                mp.y = height;
            }
            if (Eend::snapCylinderToFloor(myCylinder, myColLand, &height)) {
                if (fv < 0) fv = 0;
                mp.y = height;
            }
            glm::vec3 offset(0.0f);
            if (Eend::pushCylinderFromWall(myCylinder, myColWall, &offset)) {
                mp += offset;
            }
            */
        } 
            // adjust camera to follow
        float camDis = 60;
        myAnimatedCourt.setAnim(myAnimatedCourt.getAnim() + (0.2f * dt));
        my3DCamera.setTarget(mp.x, mp.y + 4, mp.z);
        my3DCamera.setPosition
            (mp.x + (camDis * cos(camPosX)), 
             mp.y + (camDis * sin(camPosY)), 
             mp.z + (camDis * sin(camPosX)));

        Eend::Screen::render(screenShader);
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
