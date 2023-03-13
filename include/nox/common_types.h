#pragma once

#include <cstdint>

namespace NOX {

    enum class ElementDataType {
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4
    };

    enum ImageDataType : uint32_t {
        UNSIGNED_INT8 = 0,
        FLOAT = 1
    };

    enum class TextureType {
        TEXTURE2D
    };

    enum MemoryUsage : uint32_t {
        READ_WRITE = 1 << 0,
        WRITE_ONLY = 1 << 1,
        READ_ONLY = 1 << 2,
        USE_HOST_PTR = 1 << 3,
        ALLOC_HOST_PTR = 1 << 4,
        COPY_HOST_PTR = 1 << 5
    };

} // namespace NOX
