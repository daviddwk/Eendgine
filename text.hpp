#include <string>
#include <filesystem>
#include <glm/glm.hpp>
#include <vector>
#include "entityBatches.hpp"

namespace Eendgine {
    class Text {
        public:
            Text(std::filesystem::path fontPath, unsigned int scale, std::string string);      
            ~Text();
            
            void setPosition(glm::vec3 position) { _position = position; };
            void setScale(float w, float h) { _size = glm::vec3(w, h, 1.0f); };
            
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getSize() { return _size; };
        private:
            std::vector<PanelId> _panelIds;
            glm::vec3 _position;
            glm::vec3 _size;
    };
}
