#pragma once

#include <nox/common_types.h>

#include <cstdint>

namespace NOX {

    class GLHelper {
      public:
        static uint32_t getGLType(ElementDataType type);
        static uint32_t getGLTextureType(TextureType type);
    };

} // namespace NOX
