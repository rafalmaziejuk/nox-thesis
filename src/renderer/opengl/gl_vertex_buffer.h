#pragma once

#include <nox/renderer/vertex_buffer.h>

namespace NOX {

    class GLVertexBuffer : public VertexBuffer {
      public:
        GLVertexBuffer(const void *data, const uint32_t size);
        ~GLVertexBuffer() override;

        uint32_t getHandle() const override { return m_handle; }

      private:
        uint32_t m_handle{0u};
    };

} // namespace NOX
