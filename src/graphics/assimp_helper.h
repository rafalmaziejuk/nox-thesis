#pragma once

#include <assimp/material.h>
#include <assimp/mesh.h>

#include <glm/glm.hpp>

#include <string>

namespace NOX {

    class AssimpHelper {
      public:
        [[nodiscard]] static float processFloatMaterial(const aiMaterial *material, const char *key, const uint32_t type, const uint32_t index);
        [[nodiscard]] static glm::vec3 processColorMaterial(const aiMaterial *material, const char *key, const uint32_t type, const uint32_t index);
        [[nodiscard]] static std::string processMaterialTexture(const aiMaterial *material, aiTextureType textureType, std::string_view parentPath);
    };

} // namespace NOX
