#pragma once

#include <chrono>

namespace NOX {

    class Timer {
      public:
        Timer();

        [[nodiscard]] float restart();

      private:
        std::chrono::high_resolution_clock::time_point m_startTime;
        std::chrono::high_resolution_clock::time_point m_endTime;
    };

} // namespace NOX
