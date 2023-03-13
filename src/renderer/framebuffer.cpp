#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_framebuffer.h"

#include <nox/renderer/framebuffer.h>

namespace NOX {

    std::shared_ptr<Framebuffer> Framebuffer::create(const FramebufferSpecification &spec) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_shared<GLFramebuffer>(spec);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

} // namespace NOX
