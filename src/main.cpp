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
#include <eendgine/entityBatch.hpp>
#include <eendgine/entityBatches.hpp>
#include <eendgine/shaders.hpp>

#include <stb/stb_image.h>

#include <vector>
#include <numbers>
#include <filesystem>

#include "player.hpp"
#include "ball.hpp"


namespace Eend = Eendgine;

const unsigned int screenHeight = 750;
const unsigned int screenWidth = 1000; 

int main(){
    Eend::Window::init(screenWidth, screenHeight, "Quack"); 
    Eend::Screen::init(screenWidth, screenHeight);
    Eend::FrameLimiter::setFPS(30.0f);
    glEnable(GL_DEPTH_TEST);

    
    Eend::ShaderProgram newShader("shaders/shader3D.vert", "shaders/shader3D.frag");
    Eend::Shaders shaders(
            Eend::ShaderProgram("shaders/shader.vert", "shaders/shader.frag"),
            Eend::ShaderProgram("shaders/shader3D.vert", "shaders/shader3D.frag"),
            Eend::ShaderProgram("shaders/shaderInpol.vert", "shaders/shaderInpol.frag"),
            Eend::ShaderProgram("shaders/shaderScreen.vert", "shaders/shaderScreen.frag"));

    Eend::Camera2D hudCamera(screenWidth, screenHeight);
    Eend::Camera3D sceneCamera((float)screenWidth / (float)screenHeight,
            glm::vec3(20.0f, 15.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));


    auto courtDir = std::filesystem::path("resources/court");
    
    Eend::AnimationId courtId = Eend::Entities::AnimationBatch::insert(courtDir);
    Eend::Animation& courtAnimation = Eend::Entities::AnimationBatch::getRef(courtId);
    courtAnimation.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    courtAnimation.setScale(glm::vec3(4.0f));

    Eend::EntityBatch<Eend::Sprite> newSpriteBatch;
    unsigned int newSpriteId = newSpriteBatch.insert("resources/ost/diffuse.png");
    Eend::EntityBatch<Eend::Animation> newBatch;
    unsigned int newAnimationId = newBatch.insert(courtDir);

    Eend::CollisionModel myColCourt("resources/courtCol/courtHitbox.obj");
    myColCourt.setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    myColCourt.setScale(glm::vec3(4.0f));
    
    std::vector<Eend::CollisionModel*> myColModels = {
            &myColCourt};
    
    Player player(myColModels,
            glm::vec3(0.0f, 100.0f, 0.0f),
            "resources/ost/ost.obj", sceneCamera,
            5.0f, 5.0f, 4.0f,
            10.0f, 10.0f);
    Ball ball("resources/ost/diffuse_noeyes.png", glm::vec3(0.0f, 10.0f, 0.0f), 10.0f);
    Eend::Sprite testSprite("resources/ost/diffuse.png");
    //drawBatches.insert(&testSprite);

    while(!Eend::InputManager::shouldClose){
        Eend::FrameLimiter::startInterval(); 
        Eend::Screen::bind();

        shaders.setPixelSize(5);

        float dt = Eend::FrameLimiter::deltaTime / 4;
        if (dt > 1.0f / 60.0f) dt = 1.0f / 60.0f;
        
        glm::vec3 debugPlayerStrike = player.getStrikeCollision().getPosition();
        glm::vec3 debugBallStrike = player.getPosition();
        if (player.getStrike() && Eend::colliding(player.getStrikeCollision(), ball.getCollision(), nullptr)) {
            ball.hit();
        }

        player.update(dt);
        ball.update(dt);
        
        Eend::Animation& newAnimRef = newBatch.getRef(newAnimationId);
        newAnimRef.setPosition(newAnimRef.getPosition() + 0.1f);
        Eend::Sprite& newSpriteRef = newSpriteBatch.getRef(newSpriteId);
        newSpriteRef.setScale(100.0f, 100.0f);
        newSpriteRef.setPosition(glm::vec3(10.0f, 10.0f, 10.0f));
        
        Eend::Entities::draw(shaders, hudCamera, sceneCamera);
        
        Eend::Screen::render(shaders.getShader(Eend::Shader::screen));
        Eend::InputManager::processInput();
        Eend::Window::swapBuffers(); 
        Eend::FrameLimiter::stopInterval();
    }
    return 0;
}
