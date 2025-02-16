#pragma once
#include "shader.hpp"

#include <algorithm>
#include <functional>
namespace Eendgine {

template <class E> struct entityLabeled {
        uint64_t id;
        E entity;
};

template <class E> static bool newTextureCompare(entityLabeled<E>& el1, entityLabeled<E>& el2) {
    return el1.entity.getTexture().id > el2.entity.getTexture().id;
}

template <class E> class EntityBatch {
    public:
        // assuming that you don't put two of the same in here, but not checking
        template <typename... Args> uint64_t insert(Args&&... args) {
            unsigned int _entitiesIdx = _entities.size();
            // check if already in map
            _indexMap[_nextId] = _entitiesIdx;
            _entities.emplace_back(_nextId, E(std::forward<Args>(args)...));
            // just in case these are evaluated out of order
            return _nextId++;
        }

        void erase(unsigned int id) {
            // postpose erase until right before sort
            // so that the _indexMap is always accurate
            //
            // check if it's in there here? could do it in sort

            _toEraseIds.push_back(id);
        }

        E& getRef(uint64_t id) { return _entities[_indexMap[id]].entity; }

        template <typename C> void draw(ShaderProgram& shader, C& camera) {
            EntityBatch<E>::sort();
            shader.use();
            glActiveTexture(GL_TEXTURE0);
            std::string texName = "texture_diffuse";
            glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
            unsigned int lastTexture = 0;
            unsigned int thisTexture = 0;
            for (auto ewi : EntityBatch<E>::_entities) {
                thisTexture = ewi.entity.getTexture().id;
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
            // make to erase idxs from ids
            std::vector<size_t> _toEraseIdxs(_toEraseIds.size());
            for (size_t idx = 0; idx < _toEraseIds.size(); ++idx) {
                _toEraseIdxs[idx] = _indexMap[_toEraseIds[idx]];
            }
            std::sort(_toEraseIdxs.begin(), _toEraseIdxs.end(), std::greater<int>());
            // move all to erase to end of array and erase
            for (size_t idx = 0; idx < _toEraseIdxs.size(); ++idx) {
                iter_swap(_entities.begin() + _toEraseIdxs[idx], _entities.end() - (idx + 1));
            }
            for (size_t idx = 0; idx < _toEraseIdxs.size(); ++idx) {
                size_t lastEntityIdx = _entities.size() - 1;
                _entities[lastEntityIdx].entity.eraseBuffers();
                _entities.erase(_entities.begin() + lastEntityIdx);
            }
            _toEraseIds.clear();
            _indexMap.clear();
            // sort based on texture
            std::sort(_entities.begin(), _entities.end(), newTextureCompare<E>);
            // fix index map
            for (size_t i = 0; i < _entities.size(); i++) {
                _indexMap[_entities[i].id] = i;
            }
        }
        // this probably shouldn't be a vector of pointers,
        // but I'll get around to making a real ECS later
        //
        // vector so I can control when it sorts
        std::vector<entityLabeled<E>> _entities;
        std::unordered_map<uint64_t, size_t> _indexMap;
        uint64_t _nextId = 0;
        std::vector<uint64_t> _toEraseIds;
};
} // namespace Eendgine
