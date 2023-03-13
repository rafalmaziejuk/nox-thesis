#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_vertex_buffer.h"

#include <nox/renderer/vertex_buffer.h>

namespace NOX {

    std::unique_ptr<VertexBuffer> VertexBuffer::create(const void *data, const uint32_t size) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_unique<GLVertexBuffer>(data, size);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

} // namespace NOX
