#include "assimp_helper.h"

#include "debug/debug_helpers.h"

#include "utilities/file_helper.h"

#include <nox/application.h>
#include <nox/assets/asset_manager.h>
#include <nox/graphics/model.h>
#include <nox/renderer/texture.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace NOX {

    std::shared_ptr<Model> Model::create(std::string_view name) {
        return std::make_shared<Model>(name);
    }

    Model::Model(std::string_view path) : m_parentPath(FileHelper::getParentPath(path)) {
        m_path = FileHelper::getAbsolutePath(path);

        Assimp::Importer importer;
        constexpr uint32_t flags = aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_RemoveRedundantMaterials | aiProcess_PreTransformVertices;
        const auto scene = importer.ReadFile(m_path, flags);
        NOX_ASSERT_IF((scene == nullptr) || (scene->mRootNode == nullptr) || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), "Couldn't load model {0}", path);

        NOX_ASSERT_IF(!scene->HasMeshes(), "{0} does not contain any meshes", path);

        processNode(scene, scene->mRootNode);
    }

    void Model::processNode(const aiScene *scene, const aiNode *node) {
        for (uint32_t i = 0u; i < node->mNumMeshes; i++) {
            const auto assimpMesh = scene->mMeshes[node->mMeshes[i]];
            const auto assimpMaterial = scene->mMaterials[assimpMesh->mMaterialIndex];
            m_meshes.push_back(processMesh(assimpMesh, assimpMaterial));
        }

        for (uint32_t i = 0u; i < node->mNumChildren; i++) {
            processNode(scene, node->mChildren[i]);
        }
    }

    Mesh Model::processMesh(const aiMesh *mesh, const aiMaterial *material) {
        Mesh newMesh;
        for (uint32_t i = 0u; i < mesh->mNumFaces; i++) {
            const auto &face = mesh->mFaces[i];
            NOX_ASSERT_IF((face.mNumIndices % 3u != 0u), "{0} has not been triangulated properly", m_path);

            for (uint32_t j = 0u; j < face.mNumIndices; j += 3u) {
                const auto &index0 = face.mIndices[j + 0];
                const auto &index1 = face.mIndices[j + 1];
                const auto &index2 = face.mIndices[j + 2];
                newMesh.indices.push_back(index0);
                newMesh.indices.push_back(index1);
                newMesh.indices.push_back(index2);

                Vertex v0{};
                Vertex v1{};
                Vertex v2{};
                if (mesh->HasPositions()) {
                    v0.position = {mesh->mVertices[index0].x, mesh->mVertices[index0].y, mesh->mVertices[index0].z};
                    v1.position = {mesh->mVertices[index1].x, mesh->mVertices[index1].y, mesh->mVertices[index1].z};
                    v2.position = {mesh->mVertices[index2].x, mesh->mVertices[index2].y, mesh->mVertices[index2].z};
                }

                if (mesh->HasNormals()) {
                    v0.normal = {mesh->mNormals[index0].x, mesh->mNormals[index0].y, mesh->mNormals[index0].z};
                    v1.normal = {mesh->mNormals[index1].x, mesh->mNormals[index1].y, mesh->mNormals[index1].z};
                    v2.normal = {mesh->mNormals[index2].x, mesh->mNormals[index2].y, mesh->mNormals[index2].z};
                } else {
                    const auto normal = glm::cross(v1.position - v0.position, v2.position - v0.position);
                    v0.normal = normal;
                    v1.normal = normal;
                    v2.normal = normal;
                }

                if (mesh->HasTextureCoords(0)) {
                    v0.textureCoordinates = {mesh->mTextureCoords[0][index0].x, mesh->mTextureCoords[0][index0].y};
                    v1.textureCoordinates = {mesh->mTextureCoords[0][index1].x, mesh->mTextureCoords[0][index1].y};
                    v2.textureCoordinates = {mesh->mTextureCoords[0][index2].x, mesh->mTextureCoords[0][index2].y};
                } else {
                    v0.textureCoordinates = {0.0f, 0.0f};
                    v1.textureCoordinates = {0.0f, 1.0f};
                    v2.textureCoordinates = {1.0f, 1.0f};
                }

                newMesh.vertices.push_back(v0);
                newMesh.vertices.push_back(v1);
                newMesh.vertices.push_back(v2);
            }
        }

        newMesh.materialIndex = processMaterial(material);

        return newMesh;
    }

    uint32_t Model::processMaterial(const aiMaterial *material) {
        Material newMaterial;
        newMaterial.shininess = AssimpHelper::processFloatMaterial(material, AI_MATKEY_SHININESS);
        newMaterial.refractiveIndex = AssimpHelper::processFloatMaterial(material, AI_MATKEY_REFRACTI);
        newMaterial.diffuse = AssimpHelper::processColorMaterial(material, AI_MATKEY_COLOR_DIFFUSE);
        newMaterial.ambient = AssimpHelper::processColorMaterial(material, AI_MATKEY_COLOR_AMBIENT);
        newMaterial.specular = AssimpHelper::processColorMaterial(material, AI_MATKEY_COLOR_SPECULAR);
        newMaterial.emissive = AssimpHelper::processColorMaterial(material, AI_MATKEY_COLOR_EMISSIVE);

        auto diffuseTexturePath = AssimpHelper::processMaterialTexture(material, aiTextureType_DIFFUSE, m_parentPath);
        auto specularTexturePath = AssimpHelper::processMaterialTexture(material, aiTextureType_SPECULAR, m_parentPath);
        auto normalTexturePath = AssimpHelper::processMaterialTexture(material, aiTextureType_HEIGHT, m_parentPath);
        if (!diffuseTexturePath.empty()) {
            newMaterial.diffuseMapIndex = static_cast<uint32_t>(m_texturePaths.size());
            m_texturePaths.emplace_back(diffuseTexturePath);
        }
        if (!specularTexturePath.empty()) {
            newMaterial.normalMapIndex = static_cast<uint32_t>(m_texturePaths.size());
            m_texturePaths.emplace_back(specularTexturePath);
        }
        if (!normalTexturePath.empty()) {
            newMaterial.specularMapIndex = static_cast<uint32_t>(m_texturePaths.size());
            m_texturePaths.emplace_back(normalTexturePath);
        }

        m_materials.push_back(newMaterial);
        return static_cast<uint32_t>(m_materials.size()) - 1;
    }

} // namespace NOX
