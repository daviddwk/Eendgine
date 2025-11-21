#pragma once
#include "shader.hpp"

#include <algorithm>
#include <functional>
namespace Eendgine {

using EntityId = uint64_t;

template <class E> struct EntityLabeled {
        EntityId id;
        E entity;
};

template <class E>
static bool newTextureCompare(const EntityLabeled<E>& el1, const EntityLabeled<E>& el2) {
    return el1.entity.getTexture().id > el2.entity.getTexture().id;
}

template <class E> class EntityBatch {
    public:
        // assuming that you don't put two of the same in here, but not checking
        template <typename... Args> EntityId insert(Args&&... args) {
            unsigned int m_entitiesIdx = m_entities.size();
            // check if already in map
            m_indexMap[m_nextId] = m_entitiesIdx;
            m_entities.push_back(EntityLabeled{m_nextId, E(std::forward<Args>(args)...)});
            // just in case these are evaluated out of order
            return m_nextId++;
        }

        void erase(EntityId id) {
            if (auto indexIter = m_indexMap.find(id); indexIter != std::end(m_indexMap)) {
                m_toEraseIds.push_back(id);
            }
        }

        E* getRef(EntityId id) {
            if (auto indexIter = m_indexMap.find(id); indexIter != std::end(m_indexMap)) {
                return &m_entities[indexIter->second].entity;
            }
            return NULL;
        }

        void shrink() {
            m_entities.shrink_to_fit();
            m_toEraseIds.shrink_to_fit();
        }

        template <typename C> void draw(ShaderProgram& shader, C& camera) {
            EntityBatch<E>::sort();
            shader.use();
            glActiveTexture(GL_TEXTURE0);
            std::string texName = "texture_diffuse";
            glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
            GLuint lastTexture = 0;
            GLuint thisTexture = 0;
            for (auto& labeledEntity : EntityBatch<E>::m_entities) {
                thisTexture = labeledEntity.entity.getTexture().id;
                if (lastTexture != thisTexture) {
                    glBindTexture(GL_TEXTURE_2D, thisTexture);
                }
                lastTexture = thisTexture;
                labeledEntity.entity.draw(shader.getProgramID(), camera);
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    private:
        using Entities = std::vector<EntityLabeled<E>>;
        using IndexMap = std::unordered_map<EntityId, typename Entities::size_type>;

        void sort() {
            // make to erase idxs from ids
            std::vector<typename IndexMap::size_type> m_toEraseIdxs;
            m_toEraseIdxs.reserve(m_toEraseIds.size());
            for (auto toEraseId : m_toEraseIds) {
                m_toEraseIdxs.push_back(m_indexMap[toEraseId]);
            }
            std::sort(m_toEraseIdxs.begin(), m_toEraseIdxs.end(), std::greater<int>());
            // move all to erase to end of array and erase
            for (auto toEraseIdx : m_toEraseIdxs) {
                iter_swap(m_entities.begin() + toEraseIdx, m_entities.end() - 1);
                m_entities.pop_back();
            }
            m_toEraseIds.clear();
            m_indexMap.clear();
            // sort based on texture
            std::stable_sort(m_entities.begin(), m_entities.end(), newTextureCompare<E>);
            // fix index map
            for (typename Entities::size_type idx = 0; idx < m_entities.size(); ++idx) {
                m_indexMap[m_entities[idx].id] = idx;
            }
        }
        // vector so I can control when it sorts
        Entities m_entities;
        IndexMap m_indexMap;
        EntityId m_nextId = 0;
        std::vector<EntityId> m_toEraseIds;
};
} // namespace Eendgine
