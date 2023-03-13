#pragma once

#include <cstdint>
#include <memory>

namespace NOX {

    struct FramebufferSpecification {
        uint32_t colorAttachment{0u};
    };

    class Framebuffer {
      public:
        virtual ~Framebuffer() = default;

        static std::shared_ptr<Framebuffer> create(const FramebufferSpecification &spec);

        virtual uint32_t getColorAttachmentHandle() const = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
    };

} // namespace NOX
