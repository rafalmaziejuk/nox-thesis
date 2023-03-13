#include "renderer/opengl/gl_helper.h"
#include "renderer/opengl/gl_vertex_array.h"

#include <nox/renderer/buffer_layout.h>
#include <nox/renderer/element_buffer.h>
#include <nox/renderer/vertex_buffer.h>

#include <glad/glad.h>

namespace NOX {

    GLVertexArray::GLVertexArray() {
        glCreateVertexArrays(1, &m_handle);
    }

    GLVertexArray::~GLVertexArray() {
        glDeleteVertexArrays(1, &m_handle);
    }

    void GLVertexArray::bind() const {
        glBindVertexArray(m_handle);
    }

    void GLVertexArray::setVertexBuffer(const VertexBuffer &vertexBuffer, const BufferLayout &bufferLayout) {
        constexpr GLuint vertexBufferBindingIndex = 0u;
        constexpr GLuint offsetToFirstElementInsideBuffer = 0u;
        glVertexArrayVertexBuffer(m_handle, vertexBufferBindingIndex, vertexBuffer.getHandle(), offsetToFirstElementInsideBuffer, bufferLayout.getStride());

        for (const auto &element : bufferLayout) {
            glEnableVertexArrayAttrib(m_handle, element.index);
            glVertexArrayAttribFormat(m_handle, element.index, element.dataCount, GLHelper::getGLType(element.type), element.normalized, element.offset);
            glVertexArrayAttribBinding(m_handle, element.index, vertexBufferBindingIndex);
        }
    }

    void GLVertexArray::setElementBuffer(const ElementBuffer &elementBuffer) {
        glVertexArrayElementBuffer(m_handle, elementBuffer.getHandle());
        m_count = elementBuffer.getCount();
    }

} // namespace NOX
