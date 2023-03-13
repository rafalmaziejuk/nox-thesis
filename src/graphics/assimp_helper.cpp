#include "assimp_helper.h"

#include "utilities/logger.h"

namespace NOX {

    float AssimpHelper::processFloatMaterial(const aiMaterial *material, const char *key, const uint32_t type, const uint32_t index) {
        float result = 0.0f;
        if (material->Get(key, type, index, result) == AI_SUCCESS) {
            NOX_DEBUG_LOG(TRACE, "Material {0} = {1} loaded successfully", key, result);
        } else {
            NOX_DEBUG_LOG(WARN, "{0} material not found", key);
        }

        return result;
    }

    glm::vec3 AssimpHelper::processColorMaterial(const aiMaterial *material, const char *key, const uint32_t type, const uint32_t index) {
        aiColor3D color{0.0f};
        glm::vec3 result{0.0f};
        if (material->Get(key, type, index, color) == AI_SUCCESS) {
            result.x = color.r;
            result.y = color.g;
            result.z = color.b;
            NOX_DEBUG_LOG(TRACE, "Material {0} = ({1}, {2}, {3}) loaded successfully", key, result.r, result.g, result.b);
        } else {
            NOX_DEBUG_LOG(WARN, "{0} material not found", key);
        }

        return result;
    }

    std::string AssimpHelper::processMaterialTexture(const aiMaterial *material, aiTextureType textureType, std::string_view parentPath) {
        std::string result(parentPath);
        if (material->GetTextureCount(textureType) > 0) {
            aiString assimpPath;
            material->GetTexture(textureType, 0, &assimpPath);
            std::string path(assimpPath.C_Str());
            result += '/' + path;
        } else {
            result.clear();
            NOX_DEBUG_LOG(WARN, "{0} type material texture not found", textureType);
        }

        return result;
    }

} // namespace NOX
