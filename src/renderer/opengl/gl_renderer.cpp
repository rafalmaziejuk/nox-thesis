#include "renderer/opengl/gl_built_in_shaders.h"
#include "renderer/opengl/gl_renderer.h"
#include "renderer/opengl/gl_vertex_array.h"

#include <nox/application.h>

#include <nox/assets/asset_manager.h>

#include <nox/renderer/buffer_layout.h>
#include <nox/renderer/element_buffer.h>
#include <nox/renderer/shader.h>
#include <nox/renderer/texture.h>
#include <nox/renderer/vertex_buffer.h>

#include <glad/glad.h>

namespace NOX {

    namespace {

        struct RendererData {
            void initialize() {
                constexpr float vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, // bottom left
                                              1.0f, -1.0f, 1.0f, 0.0f,  // bottom right
                                              1.0f, 1.0f, 1.0f, 1.0f,   // top right
                                              -1.0f, 1.0f, 0.0f, 1.0f}; // top left
                constexpr uint32_t indices[] = {0u, 1u, 2u,
                                                2u, 3u, 0u};

                BufferLayout bufferLayout{};
                bufferLayout.push("aPosition", ElementDataType::FLOAT2);
                bufferLayout.push("aTextureCoordinates", ElementDataType::FLOAT2);
                auto vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));
                auto elementBuffer = ElementBuffer::create(indices, sizeof(indices));

                fullscreenQuadVertexArray = std::make_unique<GLVertexArray>();
                fullscreenQuadVertexArray->setVertexBuffer(*vertexBuffer, bufferLayout);
                fullscreenQuadVertexArray->setElementBuffer(*elementBuffer);

                auto &assetManager = Application::get()->getAssetManager();
                fullscreenQuadShader = assetManager.loadAssetImmediate<Shader>("fullscreenQuad", fullscreenQuadVertexShaderSource, fullscreenQuadFragmentShaderSource);
            }

            std::unique_ptr<GLVertexArray> fullscreenQuadVertexArray{nullptr};
            std::shared_ptr<Shader> fullscreenQuadShader{nullptr};
        } s_rendererData;

        void drawIndexed(const GLVertexArray &vertexArray) {
            vertexArray.bind();
            glDrawElements(GL_TRIANGLES, vertexArray.getCount(), GL_UNSIGNED_INT, nullptr);
        }

    } // namespace

    GLRenderer::GLRenderer() {
        s_rendererData.initialize();

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void GLRenderer::setViewportSize(const uint32_t width, const uint32_t height) {
        glViewport(0, 0, width, height);
    }

    void GLRenderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderer::drawFullscreenTexture(const Texture &texture) {
        const auto &shader = *s_rendererData.fullscreenQuadShader;
        const auto &vertexArray = *s_rendererData.fullscreenQuadVertexArray;

        shader.use();
        texture.bind();
        drawIndexed(vertexArray);
    }

} // namespace NOX
