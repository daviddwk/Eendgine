#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <vector>
#include <filesystem>

#include "entityBatches.hpp"
#include "types.hpp"

namespace Eendgine {

class Particles {
    public:
        class State {
            public:
                State(Point relativePosition, Scale2D scale, unsigned int stripIdx)
                    : relativePosition(relativePosition), scale(scale), stripIdx(stripIdx) {}
                Point relativePosition;
                Scale2D scale;
                unsigned int stripIdx;
        };
        using Behavior =
            std::function<std::optional<State>(int32_t, std::chrono::milliseconds)>;
        class Properties {
            public:
                Properties(std::filesystem::path boardPath, Behavior behavior)
                : boardPath(boardPath), behavior(behavior){}
            std::filesystem::path boardPath;
            Behavior behavior;  
        };
        static void construct();
        static void destruct();
        static Particles& get();

    private:
        class Particle {
            public:
                Particle(const int seed, const BoardId id);
                int32_t seed;
                Eendgine::BoardId id;
                bool isAlive;
        };
        class Cloud {
            public:
                Cloud(Point origin, Behavior movement);
                Point origin;
                Behavior movement;
                std::chrono::time_point<std::chrono::steady_clock> start;
                bool isAlive;
                std::vector<Particle> particles;
        };

    public:
        void create(
            const Point& origin, const std::vector<Particle>::size_type count,
            const Properties properties);

        void update(const float dt);

        Particles();
        ~Particles();

    private:
        std::vector<Cloud> m_clouds;
        inline static Particles* m_instance = nullptr;
};

}
