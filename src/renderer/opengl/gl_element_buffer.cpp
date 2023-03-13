#include "renderer/opengl/gl_element_buffer.h"

#include <glad/glad.h>

namespace NOX {

    GLElementBuffer::GLElementBuffer(const uint32_t *data, const uint32_t size) : m_count(size / sizeof(uint32_t)) {
        glCreateBuffers(1, &m_handle);
        glNamedBufferStorage(m_handle, size, data, 0);
    }

    GLElementBuffer::~GLElementBuffer() {
        glDeleteBuffers(1, &m_handle);
    }

} // namespace NOX
