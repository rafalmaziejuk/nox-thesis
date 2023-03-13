#include "debug/debug_helpers.h"

#include "renderer/opengl/gl_shader.h"

#include "utilities/file_helper.h"
#include "utilities/logger.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace NOX {

    namespace {

        std::pair<std::string, std::string> parseShaderFile(std::string_view path) {
            constexpr std::string_view vertexMarker = "#vertex";
            constexpr std::string_view fragmentMarker = "#fragment";
            constexpr size_t vertexMarkerLength = vertexMarker.size();
            constexpr size_t fragmentMarkerLength = fragmentMarker.size();

            auto source = FileHelper::readFile(path);
            auto foundVertexMarker = source.find(vertexMarker) + vertexMarkerLength;
            auto foundFragmentMarker = source.find(fragmentMarker) + fragmentMarkerLength;
            auto sourceEnd = source.size();

            NOX_ASSERT_IF(foundVertexMarker == std::string::npos || foundFragmentMarker == std::string::npos, "Missing \"#vertex\" or \"#fragment\" marker in {0} shader", path);

            auto vertexSource = source.substr(foundVertexMarker, foundFragmentMarker - fragmentMarkerLength - foundVertexMarker);
            auto fragmentSource = source.substr(foundFragmentMarker, sourceEnd - foundFragmentMarker);
            return {vertexSource, fragmentSource};
        }

        bool checkCompileStatus(const uint32_t handle) {
            GLint result = GL_TRUE;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE) {
                GLint length = 0;
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);

                std::string result;
                result.resize(length);
                glGetShaderInfoLog(handle, length, nullptr, result.data());

                NOX_DEBUG_LOG(ERROR, "GLSL shader compilation error\n{0}", result);
                glDeleteShader(handle);
            }

            return result;
        }

        bool checkLinkStatus(const uint32_t handle) {
            GLint result = GL_TRUE;
            glGetProgramiv(handle, GL_LINK_STATUS, &result);

            if (result == GL_FALSE) {
                GLint length = 0;
                glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);

                std::string result;
                result.resize(length);
                glGetProgramInfoLog(handle, length, nullptr, result.data());

                NOX_DEBUG_LOG(ERROR, "GLSL program linking error\n{0}", result);
                glDeleteProgram(handle);
            }

            return result;
        }

        uint32_t compileShader(const uint32_t handle, GLenum type, const char *shaderSource) {
            uint32_t shader = glCreateShader(type);
            glShaderSource(shader, 1, &shaderSource, nullptr);
            glCompileShader(shader);
            NOX_ASSERT_IF(!checkCompileStatus(shader));
            glAttachShader(handle, shader);
            return shader;
        }

    } // namespace

    GLShader::GLShader(std::string_view path) {
        m_isReloadable = true;
        m_path = FileHelper::getAbsolutePath(path);

        const auto [vertexSource, fragmentSource] = parseShaderFile(path);
        createShaderProgram(vertexSource, fragmentSource);
    }

    GLShader::GLShader(std::string_view vertexSource, std::string_view fragmentSource) {
        createShaderProgram(vertexSource, fragmentSource);
    }

    GLShader::~GLShader() {
        glDeleteProgram(m_handle);
    }

    void GLShader::createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource) {
        m_handle = glCreateProgram();

        std::vector<uint32_t> handles{};
        handles.emplace_back(compileShader(m_handle, GL_VERTEX_SHADER, vertexSource.data()));
        handles.emplace_back(compileShader(m_handle, GL_FRAGMENT_SHADER, fragmentSource.data()));

        glLinkProgram(m_handle);
        NOX_ASSERT_IF(!checkLinkStatus(m_handle));

        for (const auto &handle : handles) {
            glDetachShader(m_handle, handle);
            glDeleteShader(handle);
        }
    }

    void GLShader::reload() {
        glDeleteProgram(m_handle);
        const auto [vertexSource, fragmentSource] = parseShaderFile(m_path);
        createShaderProgram(vertexSource, fragmentSource);
    }

    void GLShader::setFloat(std::string_view name, const float value) const {
        glUniform1f(glGetUniformLocation(m_handle, name.data()), value);
    }

    void GLShader::setFloat2(std::string_view name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(m_handle, name.data()), 1, glm::value_ptr(value));
    }

    void GLShader::setFloat3(std::string_view name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(m_handle, name.data()), 1, glm::value_ptr(value));
    }

    void GLShader::setFloat4(std::string_view name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(m_handle, name.data()), 1, glm::value_ptr(value));
    }

    void GLShader::setMat4(std::string_view name, const glm::mat4 &value) const {
        glUniformMatrix4fv(glGetUniformLocation(m_handle, name.data()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void GLShader::use() const {
        glUseProgram(m_handle);
    }

} // namespace NOX
