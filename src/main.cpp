#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera2D.hpp>
#include <eendgine/camera3D.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <eendgine/inpolModel.hpp>
#include <eendgine/model.hpp>
#include <eendgine/animatedModel.hpp>
#include <eendgine/collisionGeometry.hpp>

#include <stb/stb_image.h>
//#include "player.hpp"

#include <iostream>
#include <vector>

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
    Eend::ShaderProgram myLerpShader("shaders/shaderLerp.vert", "shaders/shaderLerp.frag");

    Eend::Camera3D my3DCamera(1000.0f / 1000.0f,
            glm::vec3(15.0f, 10.0f, 15.0f), glm::vec3(0.0f, 4.0f, 0.0f));
    
    Eend::Camera2D myCamera(1000, 1000);
    myCamera.update();
    
    Eend::Sprite mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    mySprite.setPosition(300.0f, 300.0f);
    mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    my3DSprite.setPosition(20.0f, 0.0f, 0.0f);
    my3DSprite.setSize(10.0f, 10.0f);

    //Eend::LerpModel myLerpModel("resources/ost/ost.obj", "resources/ost/ost_bent.obj", myTextureCache);
    //myLerpModel.setScale(1.0f, 1.0f, 1.0f);
    //myLerpModel.setPosition(0.0f, 0.0f, 0.0f);

    Eend::Model myModel("resources/ost_walk/ost16.obj", myTextureCache);
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(0.0f, 0.0f, 0.0f);

    std::vector<std::string> walkAnim;
    for (int i = 16; i <= 55; i++) {
        walkAnim.emplace_back("resources/ost_walk/ost" + std::to_string(i) + ".obj");
    }
    //Eend::AnimatedModel myAnimatedModel({"resources/ost/ost.obj", "resources/ost/ost_bent.obj", "resources/ost/ost.obj"}, myTextureCache);
    Eend::AnimatedModel myAnimatedModel(walkAnim, myTextureCache);
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(0.0f, 0.0f, 0.0f);
    myAnimatedModel.setRot(180.0f, 180.0f);
    
    Eend::CollisionSphere myColSphere1(0.0f, 0.0f, 2.01f, 1.0f);
    Eend::CollisionSphere myColSphere2(0.0f, 0.0f, 0.0f, 1.0f);
    
    std::cout << Eend::colliding(myColSphere1, myColSphere2) << std::endl;

    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        myAnimatedModel.draw(myLerpShader, my3DCamera);
        //myLerpModel.draw(myLerpShader, my3DCamera);
        myModel.draw(myShader3D, my3DCamera);
        my3DSprite.draw(myShader3D, my3DCamera);

        glClear(GL_DEPTH_BUFFER_BIT);

        mySprite.draw(myShader, myCamera);
        
        float dt = Eend::FrameLimiter::deltaTime;
        float speed = 100.0f;
        glm::vec2 currRot = myAnimatedModel.getRot();
        glm::vec2 currRot2 = myModel.getRot();
        if (Eendgine::InputManager::upPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            //my3DCamera.setPosition(currentCamPos.x, currentCamPos.y + (speed * dt), currentCamPos.z + (speed * dt)); 
            myAnimatedModel.setTextureIdx(0);
            //myLerpModel.setInpolScale(myLerpModel.getInpolScale() + 0.01f);
            myAnimatedModel.setRot(currRot.x + 1.0f, currRot.y);
            myModel.setRot(currRot2.x + 5.0f, currRot2.y);
            myAnimatedModel.setAnim(myAnimatedModel.getAnim() + 0.01f);
        }
        if (Eendgine::InputManager::downPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            //my3DCamera.setPosition(currentCamPos.x, currentCamPos.y - (speed * dt), currentCamPos.z - (speed * dt)); 
            myAnimatedModel.setTextureIdx(1);
            myAnimatedModel.setAnim(myAnimatedModel.getAnim() - 0.01f);
            myAnimatedModel.setRot(currRot.x, currRot.y + 1.0f);
            myModel.setRot(currRot2.x, currRot2.y + 5.0f);
            //myLerpModel.setInpolScale(myLerpModel.getInpolScale() - 0.01f);
        }
        if (Eendgine::InputManager::leftPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            my3DCamera.setPosition(currentCamPos.x + (speed * dt), currentCamPos.y, currentCamPos.z); 
        }
        if (Eendgine::InputManager::rightPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            my3DCamera.setPosition(currentCamPos.x - (speed * dt), currentCamPos.y, currentCamPos.z); 
        }

        Eend::Window::pollEvents();
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
