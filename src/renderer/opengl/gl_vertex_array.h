#pragma once

#include <cstdint>

namespace NOX {

    class ElementBuffer;
    class VertexBuffer;
    class BufferLayout;

    class GLVertexArray {
      public:
        GLVertexArray();
        ~GLVertexArray();

        void bind() const;

        void setElementBuffer(const ElementBuffer &elementBuffer);
        void setVertexBuffer(const VertexBuffer &vertexBuffer, const BufferLayout &bufferLayout);
        uint32_t getCount() const { return m_count; }

      private:
        uint32_t m_handle{0u};
        uint32_t m_count{0u};
    };

} // namespace NOX
