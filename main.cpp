#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera2D.hpp>
#include <stb/stb_image.h>

#include <iostream>

namespace Eend = Eendgine;

int main(){
    
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::Camera2D camera;
    camera.init(1000, 1000);
    camera.update();

    Eend::ShaderProgram myShader;
    myShader.init("shaders/shader.vert", "shaders/shader.frag");
    
    Eend::TextureCache texCache;

    Eend::Sprite mySprite;
    mySprite.init(100.0f, 100.0f, 100.0f, 100.0f, texCache.getTexture("resources/duck2.png"));

    mySprite.setPosition(mySprite.getX(), mySprite.getY() + 1.0f);
    mySprite.setRotation(mySprite.getRotation() + 25.0f);
    mySprite.setScale(5.0f);

    

    int i = 0;
    while(!myWindow.shouldClose()){
        myWindow.processInput();
       
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mySprite.render(&myShader, &camera);

        myWindow.pollEvents();
        myWindow.swapBuffers();
    }

    return 0;
}
