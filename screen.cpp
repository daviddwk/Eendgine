#include "fatalError.hpp"
#include "shader.hpp"

#include "screen.hpp"

namespace Eendgine {

void Screen::init(int width, int height) {
    _width = width;
    _height = height;
    /*
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_screenTriVerts), &_screenTriVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glGenFramebuffers(1, &_FB);
    glBindFramebuffer(GL_FRAMEBUFFER, _FB);

    glGenTextures(1, &_textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, _textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureColorBuffer, 0);

    glGenRenderbuffers(1, &_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        fatalError("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Screen::close() {
    // TODO somthing here I'm sure
}

void Screen::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _FB);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::render(ShaderProgram shader) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.use();
    glBindVertexArray(_VAO);
    glUniform1i(glGetUniformLocation(shader.getProgramID(), "screenTexture"), 0);
    glBindTexture(GL_TEXTURE_2D, _textureColorBuffer);

    unsigned int heightLoc = glGetUniformLocation(shader.getProgramID(), "height");
    unsigned int widthLoc = glGetUniformLocation(shader.getProgramID(), "width");
    glUniform1i(heightLoc, _height);
    glUniform1i(widthLoc, _width);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
} // namespace Eendgine
