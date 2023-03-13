#pragma once

#include <cstdint>
#include <memory>

namespace NOX {

    class RendererAPI;
    class Texture;

    class Renderer {
      public:
        static void initialize();
        static void setViewportSize(const uint32_t width, const uint32_t height);

        static void clear();
        static void drawFullscreenTexture(const Texture &texture);

      private:
        static std::unique_ptr<RendererAPI> s_rendererApi;
    };

} // namespace NOX
