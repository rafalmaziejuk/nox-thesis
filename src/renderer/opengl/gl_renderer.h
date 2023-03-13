#pragma once

#include "renderer/renderer_api.h"

namespace NOX {

    class GLRenderer : public RendererAPI {
      public:
        GLRenderer();

        void setViewportSize(const uint32_t width, const uint32_t height) override;

        void clear() override;
        void drawFullscreenTexture(const Texture &texture) override;
    };

} // namespace NOX
