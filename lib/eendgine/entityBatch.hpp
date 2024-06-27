#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "sprite.hpp"

#include <set>
#include <functional>
#include <algorithm>

namespace Eendgine {
    template<class E>
    struct entityLabeled {
        unsigned int id;
        E entity;
    };

    template<class E>
    static bool newTextureCompare(
            entityLabeled<E>& el1, 
            entityLabeled<E>& el2)
    {
        return el1.entity.getTexture() > el2.entity.getTexture();
    }

    template<class E>
    class EntityBatch {
        public:
            //assuming that you don't put two of the same in here, but not checking
            template<typename... Args>
            unsigned int insert(Args&&... args) {
                unsigned int _entitiesIdx = _entities.size();
                // check if already in map
                _indexMap[_nextIdx] = _entitiesIdx;
                _nextIdx += 1;
                _entities.emplace_back(_nextIdx, E(std::forward<Args>(args)...));
                // just in case these are evaluated out of order
                return _nextIdx;
            }

            void erase(unsigned int id) {
                // postpose erase until right before sort
                // so that the _indexMap is always accurate
                //
                // check if it's in there here? could do it in sort
                _toErase.push_back(id);
            }
            
            E* getRef(unsigned int id) {
                return &_entities[_indexMap[id]].entity;
            }

            template<typename C>
            void draw(ShaderProgram &shader, C &camera) {
                sort();
                shader.use();
                glActiveTexture(GL_TEXTURE0);
                std::string texName = "texture_diffuse";
                glUniform1i(glGetUniformLocation(
                            shader.getProgramID(), texName.c_str()), 0);
                unsigned int lastTexture = 0;
                unsigned int thisTexture = 0; 
                for (auto ewi : _entities) {
                    thisTexture = ewi.entity.getTexture(); 
                    if (lastTexture != thisTexture) {
                        glBindTexture(GL_TEXTURE_2D, thisTexture);
                    }
                    lastTexture = thisTexture;
                    ewi.entity.draw(shader.getProgramID(), camera);
                }
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        private:
            void sort() {
                // sorted greatest to largest, so that we can move later elements
                // to the end and erase them without effecting earlier elements
                std::sort(_toErase.begin(), _toErase.end(), std::greater<int>());
                for (auto idxToErase : _toErase) {
                    auto it = _indexMap.find(idxToErase);
                    if (it != _indexMap.end()){
                        // could swap to end and remove instead
                        // but having issues with swap
                        auto idxEntity = it->second;
                        _entities.erase(_entities.begin() + idxEntity);
                        _indexMap.erase(it);
                    } else {
                        // there is an issue
                    }
                }
                _toErase.clear();
                std::sort(_entities.begin(), _entities.end(), newTextureCompare<E>);
                // could try and make this map sorted so this happens in order
                for (unsigned int i = 0; i < _entities.size(); i++) {
                    _indexMap[_entities[i].id] = i;
                }
            }
            // this probably shouldn't be a vector of pointers, 
            // but I'll get around to making a real ECS later
            //
            // vector so I can control when it sorts
            std::vector<entityLabeled<E>> _entities;
            std::unordered_map<unsigned int, unsigned int> _indexMap;
            unsigned int _nextIdx = 0;
            std::vector<unsigned int> _toErase;
    };
}
