#pragma once

#include <nox/renderer/element_buffer.h>

namespace NOX {

    class GLElementBuffer : public ElementBuffer {
      public:
        GLElementBuffer(const uint32_t *data, const uint32_t size);
        ~GLElementBuffer() override;

        uint32_t getHandle() const override { return m_handle; }
        uint32_t getCount() const override { return m_count; }

      private:
        uint32_t m_handle{0u};
        uint32_t m_count{0u};
    };

} // namespace NOX
