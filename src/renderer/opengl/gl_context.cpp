#include "debug/debug_helpers.h"

#include "renderer/opengl/gl_context.h"

#include "utilities/logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace NOX {

    void GLContext::initialize() {
        auto result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NOX_ABORT_IF(!result);

        NOX_ABORT_IF(!GL_ARB_direct_state_access);

        NOX_DEBUG_LOG(INFO, "Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        NOX_DEBUG_LOG(INFO, "Device: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
        NOX_DEBUG_LOG(INFO, "OpenGL version: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

        GLint majorVersion, minorVersion;
        glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
        glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
        NOX_ABORT_IF(majorVersion < OGL_MAJOR_VERSION && minorVersion < OGL_MINOR_VERSION);
    }

} // namespace NOX
