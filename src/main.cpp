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
    collisionCube.setPosition(glm::vec3(25.0f, 1.0f, 25.0f));

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

    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        myCube.draw(myShader3D, my3DCamera);
        myModel.draw(myShader3D, my3DCamera);
        myAnimatedModel.draw(myInpolShader, my3DCamera);
        my3DSprite.draw(myShader3D, my3DCamera);
        myAnimatedModel.setAnim(myAnimatedModel.getAnim() + 0.01);

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
        if (Eend::colliding(mySphere, collisionCube, &p)) {
            mp.y += std::sqrt(2 * (p.y * p.y));
            fv = 0.0f;
            myModel.setPosition(mp.x, mp.y, mp.z);
            mySphere.setPosition(mp.x, mp.y, mp.z);
        }
        glm::vec3 spherePos = mySphere.getPosition();
        

        Eend::Window::pollEvents();
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
