#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_renderer.h"

#include <nox/renderer/renderer.h>

namespace NOX {

    std::unique_ptr<RendererAPI> Renderer::s_rendererApi = nullptr;

    void Renderer::initialize() {
        NOX_ABORT_IF(s_rendererApi != nullptr);

        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            s_rendererApi = std::make_unique<GLRenderer>();
            break;

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            break;
        }
    }

    void Renderer::setViewportSize(const uint32_t width, const uint32_t height) {
        s_rendererApi->setViewportSize(width, height);
    }

    void Renderer::clear() {
        s_rendererApi->clear();
    }

    void Renderer::drawFullscreenTexture(const Texture &texture) {
        s_rendererApi->drawFullscreenTexture(texture);
    }

} // namespace NOX
