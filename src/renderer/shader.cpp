#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_shader.h"

#include <nox/renderer/shader.h>

namespace NOX {

    std::shared_ptr<Shader> Shader::create(std::string_view path) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_shared<GLShader>(path);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

    std::shared_ptr<Shader> Shader::create(std::string_view vertexSource, std::string_view fragmentSource) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_shared<GLShader>(vertexSource, fragmentSource);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

} // namespace NOX
