#pragma once

#include "board.hpp"
#include "camera.hpp"
#include "doll.hpp"
#include "entityBatch.hpp"
#include "panel.hpp"
#include "shaders.hpp"
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

        static EntityBatch<Statue>& statues();
        static EntityBatch<Doll>& dolls();
        static EntityBatch<Board>& boards();
        static EntityBatch<Panel>& panels();

        static void draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera);

    private:
        Entities() = default;
        ~Entities() = default;
        
        inline static EntityBatch<Statue>* _statues = nullptr;
        inline static EntityBatch<Doll>* _dolls = nullptr;
        inline static EntityBatch<Board>* _boards = nullptr;
        inline static EntityBatch<Panel>* _panels = nullptr;
};

} // namespace Eendgine
