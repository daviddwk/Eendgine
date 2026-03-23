#pragma once

#include "board.hpp"
#include "camera.hpp"
#include "doll.hpp"
#include "entityBatch.hpp"
#include "panel.hpp"
#include "statue.hpp"

namespace Eendgine {
class StatueId : public EntityId {};
class DollId : public EntityId {};
class BoardId : public EntityId {};
class PanelId : public EntityId {};

class Entities {
    public:
        static void construct();
        static void destruct();

        static void shrink();

        static EntityBatch<Statue, StatueId>& statues();
        static EntityBatch<Doll, DollId>& dolls();
        static EntityBatch<Board, BoardId>& boards();
        static EntityBatch<Panel, PanelId>& panels();

        static void draw(Camera2D& hudCamera, Camera3D& sceneCamera);

    private:
        Entities() = default;
        ~Entities() = default;

        Entities(const Entities&) = delete;
        Entities& operator=(const Entities&) = delete;

        Entities(Entities&& other) = delete;
        Entities& operator=(Entities&& other) = delete;

        inline static EntityBatch<Statue, StatueId>* m_statues = nullptr;
        inline static EntityBatch<Doll, DollId>* m_dolls = nullptr;
        inline static EntityBatch<Board, BoardId>* m_boards = nullptr;
        inline static EntityBatch<Panel, PanelId>* m_panels = nullptr;
};

} // namespace Eendgine
