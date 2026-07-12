#pragma once

namespace Eendgine {

class Timer {
    public:
        Timer(float length) : m_count(0.0f), m_length(length) {};

        bool update(float dt) {
            m_count += dt;
            return m_count >= m_length;
        };
        void set(float length) { m_length = length; };
        void reset() { m_count = 0.0f; };

    private:
        float m_count;
        float m_length;
};
} // namespace Eendgine
