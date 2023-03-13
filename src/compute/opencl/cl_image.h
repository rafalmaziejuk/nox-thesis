#pragma once

#include <nox/compute/compute_image.h>

#include <cstdint>

namespace NOX {

    class CLContext;
    class Image2D;
    class Texture;

    class CLImage : public ComputeImage {
      public:
        CLImage(const CLContext &context, const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data);
        CLImage(const CLContext &context, const uint32_t usage, const Texture &texture);
        ~CLImage() override;
    };

} // namespace NOX
