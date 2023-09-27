#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <stb/stb_image.h>

#include <iostream>

namespace Eend = Eendgine;

int main(){
    
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::Shader myShader;
    myShader.init("shaders/shader.vert", "shaders/shader.frag");
    
    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    int indicies[] = {
        0, 1, 2,
        0, 2, 3
    };

    Eend::Sprite mySprite;
    mySprite.x = 0;
    mySprite.y = 0;
    mySprite.w = 1;
    mySprite.h = 1;
    
    mySprite.update();
    /*
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    */
    int i = 0;
    while(!myWindow.shouldClose()){
        //input
        myWindow.processInput();
        //render
       
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mySprite.render(&myShader);

        //myShader.use();
        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        //events and swap the buffers
        myWindow.pollEvents();
        myWindow.swapBuffers();
    }

    return 0;
}
