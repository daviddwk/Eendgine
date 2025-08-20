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
            unsigned int m_entitiesIdx = m_entities.size();
            // check if already in map
            m_indexMap[m_nextId] = m_entitiesIdx;
            m_entities.push_back(entityLabeled{m_nextId, E(std::forward<Args>(args)...)});
            // just in case these are evaluated out of order
            return m_nextId++;
        }

        void erase(unsigned int id) {
            // postpose erase until right before sort
            // so that the m_indexMap is always accurate
            //
            // check if it's in there here? could do it in sort

            m_toEraseIds.push_back(id);
        }

        E* getRef(uint64_t id) {
            if (auto it{m_indexMap.find(id)}; it != std::end(m_indexMap))
                return &m_entities[it->second].entity;
            return NULL;
        }

        template <typename C> void draw(ShaderProgram& shader, C& camera) {
            EntityBatch<E>::sort();
            shader.use();
            glActiveTexture(GL_TEXTURE0);
            std::string texName = "texture_diffuse";
            glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
            unsigned int lastTexture = 0;
            unsigned int thisTexture = 0;
            for (auto& ewi : EntityBatch<E>::m_entities) {
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
            std::vector<size_t> m_toEraseIdxs(m_toEraseIds.size());
            for (size_t idx = 0; idx < m_toEraseIds.size(); ++idx) {
                m_toEraseIdxs[idx] = m_indexMap[m_toEraseIds[idx]];
            }
            std::sort(m_toEraseIdxs.begin(), m_toEraseIdxs.end(), std::greater<int>());
            // move all to erase to end of array and erase
            for (size_t idx = 0; idx < m_toEraseIdxs.size(); ++idx) {
                iter_swap(m_entities.begin() + m_toEraseIdxs[idx], m_entities.end() - (idx + 1));
            }
            for (size_t idx = 0; idx < m_toEraseIdxs.size(); ++idx) {
                size_t lastEntityIdx = m_entities.size() - 1;
                m_entities[lastEntityIdx].entity.eraseBuffers();
                m_entities.erase(m_entities.begin() + lastEntityIdx);
            }
            m_toEraseIds.clear();
            m_indexMap.clear();
            // sort based on texture
            std::sort(m_entities.begin(), m_entities.end(), newTextureCompare<E>);
            // fix index map
            for (size_t i = 0; i < m_entities.size(); i++) {
                m_indexMap[m_entities[i].id] = i;
            }
        }
        // vector so I can control when it sorts
        std::vector<entityLabeled<E>> m_entities;
        std::unordered_map<uint64_t, size_t> m_indexMap;
        uint64_t m_nextId = 0;
        std::vector<uint64_t> m_toEraseIds;
};
} // namespace Eendgine
