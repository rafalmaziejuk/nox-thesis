#include "debug/debug_helpers.h"

#include "renderer/opengl/gl_framebuffer.h"

#include <glad/glad.h>

namespace NOX {

    GLFramebuffer::GLFramebuffer(const FramebufferSpecification &specification) : m_specification(specification) {
        glCreateFramebuffers(1, &m_handle);

        glNamedFramebufferTexture(m_handle, GL_COLOR_ATTACHMENT0, m_specification.colorAttachment, 0);

        NOX_ASSERT_IF(glCheckNamedFramebufferStatus(m_handle, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
    }

    GLFramebuffer::~GLFramebuffer() {
        glDeleteFramebuffers(1, &m_handle);
    }

    uint32_t GLFramebuffer::getColorAttachmentHandle() const {
        return m_specification.colorAttachment;
    }

    void GLFramebuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
    }

    void GLFramebuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace NOX
