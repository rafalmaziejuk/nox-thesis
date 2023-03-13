#pragma once

#include <cstdint>

namespace NOX {

    class GLContext {
      public:
        static void initialize();

      private:
        static constexpr uint8_t OGL_MAJOR_VERSION = 4;
        static constexpr uint8_t OGL_MINOR_VERSION = 6;
    };

} // namespace NOX
