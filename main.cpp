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


#include "player.hpp"

#include <iostream>
#include <vector>

namespace Eend = Eendgine;

int main(){
     
    Eend::Window::init(1000, 1000, "Quack");
    Eend::FrameLimiter::setFPS(60.0f);
   
       
    std::vector<Eend::Vertex> myVertices;
    Eend::Vertex v1;
    Eend::Vertex v2;
    Eend::Vertex v3;

    v1.setPosition(-0.5f, -0.5f, -0.5f);
    v2.setPosition( 0.5f, -0.5f, -0.5f);
    v3.setPosition( 0.5f,  0.5f, -0.5f);
    v1.setUv(0.0, 0.0);
    v2.setUv(1.0, 0.0);
    v3.setUv(0.0, 1.0);
    myVertices.push_back(v1);
    myVertices.push_back(v2);
    myVertices.push_back(v3);


    Eend::TextureCache myTextureCache;
    std::vector<unsigned int> myIndices = {0, 1, 2};
    std::vector<Eend::Texture> myTextures;
    myTextures.push_back(myTextureCache.getTexture("resources/duck.png"));

    Eend::ShaderProgram myShader3D;
    myShader3D.init("shaders/shader3D.vert", "shaders/shader3D.frag");

    Eend::Camera3D my3DCamera(1000.0f, 1000.0f,
            glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    Eend::Mesh myMesh(myVertices, myIndices, myTextures);

    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        myMesh.draw(&myShader3D, &my3DCamera);

        Eend::Window::pollEvents();
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }

    /*
    Eend::Camera2D camera;
    camera.init(1000, 1000);
    camera.update();

    Eend::ShaderProgram myShader;
    myShader.init("shaders/shader.vert", "shaders/shader.frag");

    
    Eend::TextureCache texCache;
   
    std::vector<Eend::Sprite> wallSprites;
    wallSprites.emplace_back(Eend::Sprite(-475.0f,    0.0f, 50.0f, 1000.0f, texCache.getTexture("resources/duck2.png")));
    wallSprites.emplace_back(Eend::Sprite(   0.0f,  475.0f, 1000.0f, 50.0f, texCache.getTexture("resources/duck2.png")));
    wallSprites.emplace_back(Eend::Sprite( 475.0f,    0.0f, 50.0f, 1000.0f, texCache.getTexture("resources/duck2.png")));
    wallSprites.emplace_back(Eend::Sprite(   0.0f, -475.0f, 1000.0f, 50.0f, texCache.getTexture("resources/duck2.png")));
    wallSprites.emplace_back(Eend::Sprite(   0.0f,  -300.0f, 10.0f,  10.0f, texCache.getTexture("resources/duck2.png")));

    std::vector<Eend::Texture> playerTextures;
    playerTextures.push_back(texCache.getTexture("resources/duck.png"));
    playerTextures.push_back(texCache.getTexture("resources/duck2.png"));
    Player myPlayer(100.0f, 100.0f, 100.0f, 100.0f, playerTextures);
    

    int i = 0;
    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myModel.draw(&myShader3D, &camera);
        myPlayer.draw(&myShader, &camera);
        
        for(Eend::Sprite &w : wallSprites) {
            w.draw(&myShader, &camera);
        }

        Eend::Window::pollEvents();
        Eend::InputManager::processInput();

        //myPlayer.update(wallSpritePointers);

        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    */

    return 0;
}
