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
    Eend::ShaderProgram myScreenShader("shaders/shaderScreen.vert", "shaders/shaderScreen.frag");

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
    
    /// FRAME BUFFER STUFF
    


    float screenQuadVerts[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVerts), &screenQuadVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    myScreenShader.use();
    myScreenShader.setInt("screenTexture", 0);

    // framebuffer configuration
    // -------------------------
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    // small texture to dowscale to

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    ///

    while(!Eend::InputManager::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        ///// FB
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ///// FB

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

        fv -= 0.001;
        
        if (Eendgine::InputManager::upPress) {
            // TODO fix adjustment and find out where forward actually is
            myModel.setRadians(camPosX + (std::numbers::pi / 2), 0.0f);
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
        /// FB
        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        myScreenShader.use();
        glBindVertexArray(quadVAO);
        unsigned int smallTexId = 0;
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
                                                            //
        glDrawArrays(GL_TRIANGLES, 0, 6);
        /// FB

        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    glDeleteBuffers(1, &quadVBO);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &framebuffer);
    return 0;
}
