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
#include <eendgine/info.hpp>

#include <stb/stb_image.h>

#include <vector>
#include <numbers>
#include <filesystem>

#include "player.hpp"
#include "ball.hpp"
#include "court.hpp"

namespace Eend = Eendgine;

const unsigned int screenHeight = 750;
const unsigned int screenWidth = 1000; 

int main(){
    Eend::Window::init(screenWidth, screenHeight, "Quack"); 
    Eend::Screen::init(screenWidth, screenHeight);
    Eend::Info::init();
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
    
    std::vector<Eend::CollisionModel*> myColModels;
    
    Court court(
            std::filesystem::path("resources/court"),
            std::filesystem::path("resources/courtCol/courtHitbox.obj"),
            glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(4.0f), 0.5f,
            myColModels);

    Player player(myColModels,
            glm::vec3(0.0f, 100.0f, 0.0f),
            "resources/ost/ost.obj", sceneCamera,
            5.0f, 5.0f, 4.0f,
            10.0f, 10.0f);

    Ball ball("resources/ost/diffuse_noeyes.png", glm::vec3(0.0f, 10.0f, 0.0f), 10.0f);

    Eend::Info::registerFloat("dt", INFO_OPTION_AVERAGE);
    Eend::Info::registerFloat("frame time", 0);
    
    while(!Eend::Window::shouldClose){
        Eend::FrameLimiter::startInterval(); 
        Eend::Screen::bind();

        shaders.setPixelSize(5);

        float dt = Eend::FrameLimiter::deltaTime;
        if (dt > 1.0f / 30.0f) dt = 1.0f / 30.0f;

        
        glm::vec3 debugPlayerStrike = player.getStrikeCollision().getPosition();
        glm::vec3 debugBallStrike = player.getPosition();
        if (player.getStrike() && Eend::colliding(player.getStrikeCollision(), ball.getCollision(), nullptr)) {
            ball.hit();
        }

        player.update(dt);
        ball.update(dt);
        court.update(dt);
        
        Eend::Entities::draw(shaders, hudCamera, sceneCamera);
        
        Eend::Screen::render(shaders.getShader(Eend::Shader::screen));
        Eend::Window::processInput();
        Eend::Window::swapBuffers(); 
        Eend::Info::print();
        Eend::Info::updateFloat("frame time", Eend::FrameLimiter::stopInterval());
    }
    Eend::Info::end();
    return 0;
}
