#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <eendgine/model.hpp>
#include <eendgine/collisionGeometry.hpp>

#include <stb/stb_image.h>
//#include "player.hpp"

#include <iostream>
#include <vector>
#include <numbers>

namespace Eend = Eendgine;

const unsigned int screenHeight = 1000;
const unsigned int screenWidth = 1000; 

int main(){
    Eend::Window::init(screenWidth, screenHeight, "Quack");
    Eend::FrameLimiter::setFPS(60.0f);
    
    glEnable(GL_DEPTH_TEST);

    Eend::TextureCache myTextureCache;
    
    Eend::ShaderProgram myShader("shaders/shader.vert", "shaders/shader.frag");
    Eend::ShaderProgram myShader3D("shaders/shader3D.vert", "shaders/shader3D.frag");
    Eend::ShaderProgram myInpolShader("shaders/shaderInpol.vert", "shaders/shaderInpol.frag");

    Eend::Camera3D my3DCamera(1000.0f / 1000.0f,
            glm::vec3(20.0f, 15.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
    Eend::Camera2D myCamera(1000, 1000);
    
    Eend::Sprite mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    mySprite.setPosition(300.0f, 300.0f);
    mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    my3DSprite.setPosition(20.0f, 0.0f, 0.0f);
    my3DSprite.setSize(10.0f, 10.0f);

    glm::vec3 mp = glm::vec3(0.0f, 3.0f, 0.0f);
    Eend::StaticModel myModel("resources/ost/ost.obj", myTextureCache);
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(mp.x, mp.y, mp.z);
    Eend::CollisionSphere mySphere(mp.x, mp.y, mp.z , 0.5f);
    
    Eend::CollisionModel collisionCube("resources/cube/cube.obj");
    collisionCube.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    collisionCube.setPosition(glm::vec3(100.0f, 1.0f, 100.0f));

    Eend::StaticModel myCube("resources/cube/cube.obj", myTextureCache);
    myCube.setPosition(0.0f, -5.0f, 0.0f);
    myCube.setScale(25.0f, 1.0f, 25.0f);


    std::vector<std::string> walkAnim;
    for (int i = 16; i <= 55; i++) {
        walkAnim.emplace_back("resources/ost_walk/ost" + std::to_string(i) + ".obj");
    }
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(0.0f, 0.0f, 0.0f);

    Eend::AnimatedModel myAnimatedModel(walkAnim, myTextureCache);
    myAnimatedModel.setPosition(0.0f, 0.0f, 0.0f);
    myAnimatedModel.setScale(0.8f, 0.8f, 0.8f);
    myAnimatedModel.setAnim(0.0f);
    
    float fv = 0.0f;
    float camPosX = 0;
    float camPosY = 0;

    while(!Eend::InputManager::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // drawing 3D
        myCube.draw(myShader3D, my3DCamera);
        myModel.draw(myShader3D, my3DCamera);
        myAnimatedModel.draw(myInpolShader, my3DCamera);
        my3DSprite.draw(myShader3D, my3DCamera);
        myAnimatedModel.setAnim(myAnimatedModel.getAnim() + 0.01);

        glClear(GL_DEPTH_BUFFER_BIT);
        // drawing HUD
        mySprite.draw(myShader, myCamera);
        
        float dt = Eend::FrameLimiter::deltaTime;
        float speed = 0.001f;
        // move based on input and gravity
        camPosX += Eend::InputManager::deltaMouseX / 100.0f;
        camPosY += Eend::InputManager::deltaMouseY / 100.0f;
        if (camPosY > 3.14 * 0.5) {
            camPosY = 3.14 * 0.5;
        } else if (camPosY < -(3.14 * 0.1)) {
            camPosY = -(3.14 * 0.1);
        }
        fv -= 0.001;
        
        if (Eendgine::InputManager::upPress) {
            // TODO fix adjustment and find out where forward actually is
            myModel.setRadians(camPosX + (3.1415 / 2), 0.0f);
            mp.x -= (speed * cos(camPosX)) / dt;
            mp.z -= (speed * sin(camPosX)) / dt;
        }
        if (Eendgine::InputManager::downPress) {
            mp.x += (speed * cos(camPosX)) / dt;
            mp.z += (speed * sin(camPosX)) / dt;
        }
        if (Eendgine::InputManager::leftPress) {
            mp.x -= (speed * sin(camPosX)) / dt;
            mp.z += (speed * cos(camPosX)) / dt;
        }
        if (Eendgine::InputManager::rightPress) {
            mp.x += (speed * sin(camPosX)) / dt;
            mp.z -= (speed * cos(camPosX)) / dt;
        }
        
        mp.y += fv;
        myModel.setPosition(mp.x, mp.y, mp.z);
        mySphere.setPosition(mp.x, mp.y, mp.z);
        // adjust for collisions
        glm::vec3 p;
        if (Eend::colliding(mySphere, collisionCube, &p)) {
            mp.y += std::sqrt(2 * (p.y * p.y));
            fv = 0.0f;
            myModel.setPosition(mp.x, mp.y, mp.z);
            mySphere.setPosition(mp.x, mp.y, mp.z);
        }
        glm::vec3 spherePos = mySphere.getPosition();

        // adjust camera to follow
        float camDis = 30;
        my3DCamera.setTarget(mp.x, mp.y, mp.z);
        my3DCamera.setPosition
            (mp.x + (camDis * cos(camPosX)), 
             mp.y + (camDis * sin(camPosY)), 
             mp.z + (camDis * sin(camPosX)));
        myAnimatedModel.setPosition(
                (float)Eend::InputManager::deltaMouseX / dt / 1000,
                (float)Eend::InputManager::deltaMouseY / dt / 1000,
                0.0f);
        

        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
