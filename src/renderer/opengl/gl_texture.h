#pragma once

#include <nox/common_types.h>

#include <nox/renderer/texture.h>

namespace NOX {

    class GLTexture2D : public Texture2D {
      public:
        GLTexture2D(const uint32_t width, const uint32_t height);
        GLTexture2D(std::string_view path);
        ~GLTexture2D() override;

        void reload() override;

        uint32_t getHandle() const override { return m_handle; }
        uint32_t getWidth() const override { return m_width; }
        uint32_t getHeight() const override { return m_height; }

        void bind(const uint32_t unit = 0u) const override;

      private:
        void createTexture();

      private:
        uint32_t m_handle{0u};
        uint32_t m_width{0u};
        uint32_t m_height{0u};
    };

} // namespace NOX
