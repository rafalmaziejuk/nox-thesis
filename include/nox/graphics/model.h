#pragma once

#include <nox/assets/asset.h>

#include <glm/glm.hpp>

#include <memory>

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace NOX {

    class Texture;

    struct Vertex {
        glm::vec3 position{0.0f};
        glm::vec3 normal{0.0f};
        glm::vec2 textureCoordinates{0.0f};
    };

    struct Material {
        float shininess{0.0f};
        float refractiveIndex{0.0f};
        glm::vec3 diffuse{0.0f};
        glm::vec3 ambient{0.0f};
        glm::vec3 specular{0.0f};
        glm::vec3 emissive{0.0f};

        uint32_t diffuseMapIndex;
        uint32_t normalMapIndex;
        uint32_t specularMapIndex;
    };

    struct Mesh {
        uint32_t materialIndex;
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };

    class Model : public Asset {
      public:
        explicit Model(std::string_view path);

        static std::shared_ptr<Model> create(std::string_view path);

        const std::vector<Mesh> &getMeshes() const { return m_meshes; }
        const std::vector<Material> &getMaterials() const { return m_materials; }
        const std::vector<std::string> &getTexturePaths() const { return m_texturePaths; }

      private:
        void processNode(const aiScene *scene, const aiNode *node);
        Mesh processMesh(const aiMesh *mesh, const aiMaterial *material);
        uint32_t processMaterial(const aiMaterial *material);

      private:
        std::string m_parentPath;
        std::vector<Mesh> m_meshes;
        std::vector<Material> m_materials;
        std::vector<std::string> m_texturePaths;
    };

} // namespace NOX
