#include "timer.h"

namespace NOX {

    Timer::Timer() : m_startTime(std::chrono::high_resolution_clock::now()) {}

    float Timer::restart() {
        m_endTime = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration<float>(m_endTime - m_startTime);
        m_startTime = std::chrono::high_resolution_clock::now();
        return delta.count();
    }

} // namespace NOX
