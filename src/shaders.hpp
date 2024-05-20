#include <eendgine/renderBatch.hpp>
#include <eendgine/shader.hpp>

namespace Eend = Eendgine;

enum Shader{sprite, model, animation, screen};
class Shaders {
    public:
        Shaders(Eend::ShaderProgram spriteShader,
                Eend::ShaderProgram modelShader,
                Eend::ShaderProgram animationShader,
                Eend::ShaderProgram screenShader);
        Eend::ShaderProgram& getShader(Shader shader);
        void setPixelSize(uint pixelSize);
    private:
        Eend::ShaderProgram _spriteShader;
        Eend::ShaderProgram _modelShader;
        Eend::ShaderProgram _animationShader;
        Eend::ShaderProgram _screenShader;
};

