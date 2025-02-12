#pragma once

#include "board.hpp"
#include "camera.hpp"
#include "doll.hpp"
#include "entityBatch.hpp"
#include "panel.hpp"
#include "shaders.hpp"
#include "statue.hpp"

#include <filesystem>

namespace Eendgine {
using StatueId = unsigned int;
using DollId = unsigned int;
using BoardId = unsigned int;
using PanelId = unsigned int;

class Entities {
    public:
        class StatueBatch {
            public:
                static StatueId insert(const std::filesystem::path statuePath) {
                    return _statues.insert(statuePath);
                };
                static void erase(const StatueId id) { _statues.erase(id); };
                static Statue& getRef(const StatueId id) { return _statues.getRef(id); }
        };
        class DollBatch {
            public:
                static DollId insert(const std::filesystem::path dollPath) {
                    return _dolls.insert(dollPath);
                };
                static void erase(const DollId id) { _dolls.erase(id); };
                static Doll& getRef(const DollId id) { return _dolls.getRef(id); }
        };
        class BoardBatch {
            public:
                static BoardId insert(const std::filesystem::path boardPath) {
                    return _boards.insert(boardPath);
                };
                static void erase(const BoardId id) { _boards.erase(id); };
                static Board& getRef(const BoardId id) { return _boards.getRef(id); }
        };
        class PanelBatch {
            public:
                static PanelId insert(const std::filesystem::path panelPath) {
                    return _panels.insert(panelPath);
                };
                static void erase(const PanelId id) { _panels.erase(id); };
                static Panel& getRef(const PanelId id) { return _panels.getRef(id); }
        };
        static void draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera);

    private:
        inline static EntityBatch<Statue> _statues;
        inline static EntityBatch<Doll> _dolls;
        inline static EntityBatch<Board> _boards;
        inline static EntityBatch<Panel> _panels;
};
} // namespace Eendgine
