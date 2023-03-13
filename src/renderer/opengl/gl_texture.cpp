#include "debug/debug_helpers.h"

#include "renderer/opengl/gl_texture.h"

#include "utilities/file_helper.h"

#include <nox/graphics/image.h>

#include <glad/glad.h>

namespace NOX {

    GLTexture2D::GLTexture2D(const uint32_t width, const uint32_t height) : m_width(width),
                                                                            m_height(height) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        glTextureStorage2D(m_handle, 1, GL_RGBA8, m_width, m_height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    GLTexture2D::GLTexture2D(std::string_view path) {
        m_isReloadable = true;
        m_path = FileHelper::getAbsolutePath(path);

        createTexture();
    }

    GLTexture2D::~GLTexture2D() {
        glDeleteTextures(1, &m_handle);
    }

    void GLTexture2D::createTexture() {
        Image2D image(m_path);
        const auto &channels = image.getChannels();
        const auto &imageData = image.getData<uint8_t>();

        m_width = image.getWidth();
        m_height = image.getHeight();

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
        if (channels == 1) {
            internalFormat = GL_R8;
            dataFormat = GL_RED;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        } else if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        glTextureStorage2D(m_handle, 1, internalFormat, m_width, m_height);
        glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, imageData.data());
        glGenerateTextureMipmap(m_handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void GLTexture2D::reload() {
        glDeleteTextures(1, &m_handle);
        createTexture();
    }

    void GLTexture2D::bind(const uint32_t unit) const {
        glBindTextureUnit(unit, m_handle);
    }

} // namespace NOX
