#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>

#include <iostream>

namespace Eend = Eendgine;

int main(){
    
    Eend::Window myWindow;
    myWindow.init(1000, 1000, "Quack");
    
    Eend::ShaderProgram myShaderProgram;
    myShaderProgram.init("shaders/shader.vert", "shaders/shader.frag");
    

    int i = 0;
    while(!myWindow.shouldClose()){
        //input
        myWindow.processInput();
        //render
        
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float verticies[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
		

        
        //events and swap the buffers
        myWindow.pollEvents();
        myWindow.swapBuffers();
    }

    return 0;
}
