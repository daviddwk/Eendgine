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
            glm::vec3(15.0f, 10.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
    Eend::Camera2D myCamera(1000, 1000);
    myCamera.update();
    
    Eend::Sprite mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    mySprite.setPosition(300.0f, 300.0f);
    mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    my3DSprite.setPosition(20.0f, 0.0f, 0.0f);
    my3DSprite.setSize(10.0f, 10.0f);

    

    glm::vec3 mp = glm::vec3(0.0f, 3.0f, 0.0f);
    Eend::Model myModel("resources/cube/cube.obj", myTextureCache);
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(mp.x, mp.y, mp.z);
    Eend::CollisionSphere mySphere(mp.x, mp.y, mp.z , 0.5f);
    Eend::CollisionPlane myPlane;
    glm::vec3 planeNormal(0.8f, 1.0f, 0.8f);
    planeNormal = glm::normalize(planeNormal);
    myPlane.setNormal(planeNormal.x, planeNormal.y, planeNormal.z);
    myPlane.setPosition(0.0f, 0.0f, 0.0f);

    
    /*
    std::vector<std::string> walkAnim;
    for (int i = 16; i <= 55; i++) {
        walkAnim.emplace_back("resources/ost_walk/ost" + std::to_string(i) + ".obj");
    }
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(0.0f, 0.0f, 0.0f);
    myAnimatedModel.setRot(180.0f, 180.0f);
    */

    
    float fv = 0.0f;

    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        myModel.draw(myShader3D, my3DCamera);
        my3DSprite.draw(myShader3D, my3DCamera);

        glClear(GL_DEPTH_BUFFER_BIT);

        mySprite.draw(myShader, myCamera);
        
        float dt = Eend::FrameLimiter::deltaTime;
        float speed = 100.0f;
        
        fv -= 0.001;
        if (Eendgine::InputManager::upPress) {
            mp.x -= 0.02;
        }
        if (Eendgine::InputManager::downPress) {
            mp.x += 0.02;
        }
        if (Eendgine::InputManager::leftPress) {
            mp.z += 0.02;
        }
        if (Eendgine::InputManager::rightPress) {
            mp.z -= 0.02;
        }
        
        mp.y += fv;
        myModel.setPosition(mp.x, mp.y, mp.z);
        mySphere.setPosition(mp.x, mp.y, mp.z);

        glm::vec3 p;
        if (Eend::colliding(mySphere, myPlane, &p)) {
            std::cout << "colliding" << std::endl;
            std::cout << p.x << ' ' << p.y << ' ' << p.z << std::endl;
            mp -= p;
            fv = 0.0f;
            myModel.setPosition(mp.x, mp.y, mp.z);
            mySphere.setPosition(mp.x, mp.y, mp.z);
        }
        //std::cout << "location" << std::endl;
        //std::cout << mp.x << ' ' << mp.y << ' ' << mp.z << std::endl;

        

        Eend::Window::pollEvents();
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
