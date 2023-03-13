#pragma once

#include <nox/renderer/framebuffer.h>

namespace NOX {

    class GLFramebuffer : public Framebuffer {
      public:
        GLFramebuffer(const FramebufferSpecification &spec);
        ~GLFramebuffer() override;

        uint32_t getColorAttachmentHandle() const override;

        void bind() const override;
        void unbind() const override;

      private:
        uint32_t m_handle{0u};
        FramebufferSpecification m_specification{};
    };

} // namespace NOX
