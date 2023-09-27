#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>

#include <iostream>

namespace Eend = Eendgine;

int main(){
    
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::ShaderProgram myShaderProgram;
    myShaderProgram.init("shaders/shader.vert", "shaders/shader.frag");
    
    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    

    int i = 0;
    while(!myWindow.shouldClose()){
        //input
        myWindow.processInput();
        //render
       
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShaderProgram.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //events and swap the buffers
        myWindow.pollEvents();
        myWindow.swapBuffers();

    }

    return 0;
}
