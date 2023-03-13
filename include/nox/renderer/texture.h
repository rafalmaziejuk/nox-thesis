#pragma once

#include <nox/common_types.h>

#include <nox/assets/asset.h>

#include <memory>

namespace NOX {

    class Texture : public Asset {
      public:
        ~Texture() override = default;

        virtual uint32_t getHandle() const = 0;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
        virtual TextureType getType() const = 0;

        virtual void bind(uint32_t unit = 0u) const = 0;
    };

    class Texture2D : public Texture {
      public:
        ~Texture2D() override = default;

        static std::shared_ptr<Texture2D> create(const uint32_t width, const uint32_t height);
        static std::shared_ptr<Texture2D> create(std::string_view path);

        TextureType getType() const override { return TextureType::TEXTURE2D; }
    };

} // namespace NOX
