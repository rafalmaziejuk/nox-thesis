#pragma once

#include <nox/renderer/shader.h>

namespace NOX {

    class GLShader : public Shader {
      public:
        GLShader(std::string_view path);
        GLShader(std::string_view vertexSource, std::string_view fragmentSource);
        ~GLShader() override;

        void reload() override;

        void setFloat(std::string_view name, const float value) const override;
        void setFloat2(std::string_view name, const glm::vec2 &value) const override;
        void setFloat3(std::string_view name, const glm::vec3 &value) const override;
        void setFloat4(std::string_view name, const glm::vec4 &value) const override;
        void setMat4(std::string_view name, const glm::mat4 &value) const override;

        void use() const override;

      private:
        void createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);

      private:
        uint32_t m_handle{0u};
    };

} // namespace NOX
