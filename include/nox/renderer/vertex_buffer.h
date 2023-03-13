#pragma once

#include <cstdint>
#include <memory>

namespace NOX {

    class VertexBuffer {
      public:
        virtual ~VertexBuffer() = default;

        static std::unique_ptr<VertexBuffer> create(const void *data, const uint32_t size);

        virtual uint32_t getHandle() const = 0;
    };

} // namespace NOX
