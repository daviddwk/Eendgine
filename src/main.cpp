#include <eendgine/window.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera.hpp>
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>
#include <eendgine/model.hpp>
#include <eendgine/collisionGeometry.hpp>
#include <eendgine/screen.hpp>
#include <eendgine/drawBatch.hpp>

#include <stb/stb_image.h>
//#include "player.hpp"

#include <vector>
#include <numbers>

#include "shaders.hpp"
#include "drawBatches.hpp"
#include "player.hpp"


namespace Eend = Eendgine;

const unsigned int screenHeight = 750;
const unsigned int screenWidth = 1000; 

int main(){
    Eend::Window::init(screenWidth, screenHeight, "Quack"); 
    Eend::Screen::init(screenWidth, screenHeight);
    Eend::FrameLimiter::setFPS(30.0f);
    glEnable(GL_DEPTH_TEST);

    Eend::TextureCache myTextureCache;
    
    Shaders shaders(
            Eend::ShaderProgram("shaders/shader.vert", "shaders/shader.frag"),
            Eend::ShaderProgram("shaders/shader3D.vert", "shaders/shader3D.frag"),
            Eend::ShaderProgram("shaders/shaderInpol.vert", "shaders/shaderInpol.frag"),
            Eend::ShaderProgram("shaders/shaderScreen.vert", "shaders/shaderScreen.frag"));

    Eend::Camera2D hudCamera(screenWidth, screenHeight);
    Eend::Camera3D sceneCamera((float)screenWidth / (float)screenHeight,
            glm::vec3(20.0f, 15.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    DrawBatches drawBatches;
    
    //Eend::Sprite2D mySprite(myTextureCache.getTexture("resources/ost/diffuse.png"), myCamera);
    //mySprite.setPosition(300.0f, 300.0f);
    //mySprite.setSize(100.0f, 100.0f);

    Eend::Sprite3D my3DSprite(myTextureCache.getTexture("resources/ost/diffuse.png"), sceneCamera);
    my3DSprite.setPosition(glm::vec3(10.0f, 10.0f, 10.0f));
    my3DSprite.setSize(10.0f, 10.0f);


    std::vector<std::string> courtAnim;
    for (int i = 1; i <= 4; i++) {
        courtAnim.emplace_back("resources/court/court" + std::to_string(i) + ".obj");
    }

    Eend::AnimatedModel myAnimatedCourt(courtAnim, myTextureCache, sceneCamera);
    myAnimatedCourt.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    myAnimatedCourt.setScale(glm::vec3(4.0f));
    myAnimatedCourt.setAnim(0.0f);
    
    //myRenderBatch.insertModel(&myAnimatedCourt);
    drawBatches.insert(&myAnimatedCourt); 
    drawBatches.insert(&my3DSprite);

    Eend::CollisionModel myColCourt("resources/courtCol/courtHitbox.obj");
    myColCourt.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    myColCourt.setScale(glm::vec3(4.0f));
    
    
    std::vector<Eend::CollisionModel*> myColModels = {
            &myColCourt};

    Player player(drawBatches, myColModels,
            glm::vec3(0.0f, 10.0f, 0.0f),
            "resources/ost/ost.obj", myTextureCache, sceneCamera,
            5.0f, 5.0f, 5.0f,
            10.0f, 20.0f);

    while(!Eend::InputManager::shouldClose){
        Eend::FrameLimiter::startInterval(); 
        Eend::Screen::bind();

        shaders.setPixelSize(5);

        float dt = Eend::FrameLimiter::deltaTime / 4;
        if (dt > 1.0f / 60.0f) dt = 1.0f / 60.0f;
        myAnimatedCourt.setAnim(myAnimatedCourt.getAnim() + (0.2f * dt));

        player.update(dt);

        drawBatches.draw(shaders); 

        Eend::Screen::render(shaders.getShader(Shader::screen));
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
