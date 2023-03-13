#pragma once

#include <cstdint>

namespace NOX {

    class Texture;

    class RendererAPI {
      public:
        enum class API {
            OPENGL
        };

      public:
        virtual void setViewportSize(const uint32_t width, const uint32_t height) = 0;

        virtual void clear() = 0;
        virtual void drawFullscreenTexture(const Texture &texture) = 0;

        static API getRendererApi() { return s_rendererApi; }

      private:
        static API s_rendererApi;
    };

} // namespace NOX
