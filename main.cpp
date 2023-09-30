#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera2D.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <stb/stb_image.h>

#include "player.hpp"

#include <iostream>
#include <vector>

namespace Eend = Eendgine;

int main(){
     
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::FrameLimiter frameLimiter;
    frameLimiter.setFPS(60.0f);
    
    Eend::InputManager inMan;

    Eend::Camera2D camera;
    camera.init(1000, 1000);
    camera.update();

    Eend::ShaderProgram myShader;
    myShader.init("shaders/shader.vert", "shaders/shader.frag");
    
    Eend::TextureCache texCache;
   
    Eend::Sprite wallSprites[5];
    wallSprites[0].init(-475.0f,    0.0f, 50.0f, 1000.0f, texCache.getTexture("resources/duck2.png"));
    wallSprites[1].init(   0.0f,  475.0f, 1000.0f, 50.0f, texCache.getTexture("resources/duck2.png"));
    wallSprites[2].init( 475.0f,    0.0f, 50.0f, 1000.0f, texCache.getTexture("resources/duck2.png"));
    wallSprites[3].init(   0.0f, -475.0f, 1000.0f, 50.0f, texCache.getTexture("resources/duck2.png"));
    wallSprites[4].init(   0.0f,  -300.0f, 10.0f,  10.0f, texCache.getTexture("resources/duck2.png"));

    std::vector<Eend::Sprite *> wallSpritePointers;
    for(int i = 0; i < 5; i++){
        wallSpritePointers.push_back(&wallSprites[i]);
    }

    Player myPlayer;
    myPlayer.init(100.0f, 100.0f, 100.0f, 100.0f, texCache.getTexture("resources/duck2.png"));
    
    

    int i = 0;
    while(!myWindow.shouldClose){
        frameLimiter.startInterval(); 
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        myPlayer.render(&myShader, &camera);
        
        for(int i = 0; i < wallSpritePointers.size(); i++){
            wallSprites[i].render(&myShader, &camera);
        }

        myWindow.pollEvents();
        inMan.processInput();

        myPlayer.update(&inMan, wallSpritePointers);

        myWindow.swapBuffers(); 
        

        frameLimiter.stopInterval();
    }

    return 0;
}
