#include "debug/debug_helpers.h"

#include "renderer/renderer_api.h"
#include "renderer/opengl/gl_element_buffer.h"

#include <nox/renderer/element_buffer.h>

namespace NOX {

    std::unique_ptr<ElementBuffer> ElementBuffer::create(const uint32_t *data, const uint32_t size) {
        switch (RendererAPI::getRendererApi()) {
        case RendererAPI::API::OPENGL:
            return std::make_unique<GLElementBuffer>(data, size);

        default:
            NOX_ASSERT_IF(true, "This renderer API is not supported");
            return nullptr;
        }
    }

} // namespace NOX
