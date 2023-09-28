#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <stb/stb_image.h>

#include <iostream>

namespace Eend = Eendgine;

int main(){
    
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::Shader myShader;
    myShader.init("shaders/shader.vert", "shaders/shader.frag");
    
    Eend::TextureCache texCache;

    Eend::Sprite mySprite;
    mySprite.init(0.0f, 0.0f, 1.0f, 1.0f, texCache.getTexture("duck.png"));

    mySprite.setPosition(mySprite.getX(), mySprite.getY() + 1.0f);
    mySprite.setRotation(mySprite.getRotation() + 25.0f);
    mySprite.setScale(mySprite.getScale() + 0.5f);

    Eend::Sprite mySprite1;
    mySprite1.init(0.8, 0.8, 0.4, 0.4, texCache.getTexture("duck.png"));
    

    int i = 0;
    while(!myWindow.shouldClose()){
        myWindow.processInput();
       
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mySprite.render(&myShader);
        mySprite1.render(&myShader);

        myWindow.pollEvents();
        myWindow.swapBuffers();
    }

    return 0;
}
