#pragma once

#include <nox/assets/asset.h>

#include <glm/glm.hpp>

#include <memory>

namespace NOX {

    class Shader : public Asset {
      public:
        virtual ~Shader() = default;

        static std::shared_ptr<Shader> create(std::string_view path);
        static std::shared_ptr<Shader> create(std::string_view vertexSource, std::string_view fragmentSource);

        virtual void setFloat(std::string_view name, const float value) const = 0;
        virtual void setFloat2(std::string_view name, const glm::vec2 &value) const = 0;
        virtual void setFloat3(std::string_view name, const glm::vec3 &value) const = 0;
        virtual void setFloat4(std::string_view name, const glm::vec4 &value) const = 0;
        virtual void setMat4(std::string_view name, const glm::mat4 &value) const = 0;

        virtual void use() const = 0;
    };

} // namespace NOX
