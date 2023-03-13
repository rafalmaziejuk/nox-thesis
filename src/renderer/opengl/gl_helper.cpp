#include "debug/debug_helpers.h"

#include "renderer/opengl/gl_helper.h"

#include <glad/glad.h>

namespace NOX {

    uint32_t GLHelper::getGLType(ElementDataType type) {
        switch (type) {
        case ElementDataType::FLOAT:
        case ElementDataType::FLOAT2:
        case ElementDataType::FLOAT3:
        case ElementDataType::FLOAT4:
            return GL_FLOAT;

        default:
            NOX_ASSERT_IF(true);
            return 0u;
        }
    }

    uint32_t GLHelper::getGLTextureType(TextureType type) {
        switch (type) {
        case TextureType::TEXTURE2D:
            return GL_TEXTURE_2D;

        default:
            NOX_ABORT_IF(true);
            return 0u;
        }
    }

} // namespace NOX
