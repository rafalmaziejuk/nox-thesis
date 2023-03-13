#include "renderer/opengl/gl_vertex_buffer.h"

#include <glad/glad.h>

namespace NOX {

    GLVertexBuffer::GLVertexBuffer(const void *data, const uint32_t size) {
        glCreateBuffers(1, &m_handle);
        glNamedBufferStorage(m_handle, size, data, 0);
    }

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &m_handle);
    }

} // namespace NOX
