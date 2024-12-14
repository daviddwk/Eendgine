#pragma once

#include "camera.hpp"
#include "doll.hpp"
#include "entityBatch.hpp"
#include "shaders.hpp"
#include "sprite.hpp"
#include "statue.hpp"

#include <filesystem>

namespace Eendgine {
using StatueId = unsigned int;
using DollId = unsigned int;
using BoardId = unsigned int;
using PanelId = unsigned int;

using Board = Sprite;
using Panel = Sprite;

class Entities {
    public:
        class StatueBatch {
            public:
                static StatueId insert(std::filesystem::path statuePath) {
                    return _statues.insert(statuePath);
                };
                static void erase(StatueId id) { _statues.erase(id); };
                static Statue& getRef(StatueId id) { return _statues.getRef(id); }
        };
        class DollBatch {
            public:
                static DollId insert(std::filesystem::path modelsDir) {
                    return _dolls.insert(modelsDir);
                };
                static void erase(DollId id) { _dolls.erase(id); };
                static Doll& getRef(DollId id) { return _dolls.getRef(id); }
        };
        class BoardBatch {
            public:
                static BoardId insert(std::filesystem::path boardPath) {
                    return _boards.insert(boardPath);
                };
                static void erase(BoardId id) { _boards.erase(id); };
                static Board& getRef(BoardId id) { return _boards.getRef(id); }
        };
        class PanelBatch {
            public:
                static PanelId insert(std::filesystem::path panelPath) {
                    return _panels.insert(panelPath);
                };
                static void erase(PanelId id) { _panels.erase(id); };
                static Panel& getRef(PanelId id) { return _panels.getRef(id); }
        };
        static void draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera);

    private:
        inline static EntityBatch<Statue> _statues;
        inline static EntityBatch<Doll> _dolls;
        inline static EntityBatch<Board> _boards;
        inline static EntityBatch<Panel> _panels;
};
} // namespace Eendgine
