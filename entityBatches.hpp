#pragma once

#include "board.hpp"
#include "camera.hpp"
#include "doll.hpp"
#include "entityBatch.hpp"
#include "panel.hpp"
#include "statue.hpp"

namespace Eendgine {
using StatueId = uint64_t;
using DollId = uint64_t;
using BoardId = uint64_t;
using PanelId = uint64_t;

class Entities {
    public:
        static void construct();
        static void destruct();

        static void shrink();

        static EntityBatch<Statue>& statues();
        static EntityBatch<Doll>& dolls();
        static EntityBatch<Board>& boards();
        static EntityBatch<Panel>& panels();

        static void draw(Camera2D& hudCamera, Camera3D& sceneCamera);

    private:
        Entities() = default;
        ~Entities() = default;

        inline static EntityBatch<Statue>* m_statues = nullptr;
        inline static EntityBatch<Doll>* m_dolls = nullptr;
        inline static EntityBatch<Board>* m_boards = nullptr;
        inline static EntityBatch<Panel>* m_panels = nullptr;
};

} // namespace Eendgine
