#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera2D.hpp>
#include <eendgine/camera3D.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <eendgine/model.hpp>
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

    Eend::Camera3D my3DCamera(1000.0f / 1000.0f,
            glm::vec3(15.0f, 10.0f, 15.0f), glm::vec3(0.0f, 4.0f, 0.0f));
    
    Eend::Camera2D myCamera(1000, 1000);
    myCamera.update();
    
    Eend::Sprite mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    mySprite.setPosition(300.0f, 300.0f);
    mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"));
    my3DSprite.setPosition(0.0f, 0.0f, 0.0f);
    my3DSprite.setSize(10.0f, 10.0f);

    Eend::Model myModel("resources/ost/ost.obj", myTextureCache);
    myModel.setScale(1.0f, 1.0f, 1.0f);
    myModel.setPosition(0.0f, 0.0f, 0.0f);

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
        if (Eendgine::InputManager::upPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            my3DCamera.setPosition(currentCamPos.x, currentCamPos.y + (speed * dt), currentCamPos.z + (speed * dt)); 
            myModel.setTextureIdx(0);
        }
        if (Eendgine::InputManager::downPress) {
            glm::vec3 currentCamPos = my3DCamera.getPosition();
            my3DCamera.setPosition(currentCamPos.x, currentCamPos.y - (speed * dt), currentCamPos.z - (speed * dt)); 
            myModel.setTextureIdx(1);
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
