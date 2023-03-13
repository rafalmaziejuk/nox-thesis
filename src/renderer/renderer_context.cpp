#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/renderer_context.h"
#include "renderer/opengl/gl_context.h"

namespace NOX {

    void RendererContext::initialize() {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            GLContext::initialize();
            break;

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            break;
        }
    }

} // namespace NOX
