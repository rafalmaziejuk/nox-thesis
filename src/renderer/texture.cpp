#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_texture.h"

#include <nox/renderer/texture.h>

namespace NOX {

    std::shared_ptr<Texture2D> Texture2D::create(const uint32_t width, const uint32_t height) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_shared<GLTexture2D>(width, height);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

    std::shared_ptr<Texture2D> Texture2D::create(std::string_view path) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_shared<GLTexture2D>(path);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

} // namespace NOX
