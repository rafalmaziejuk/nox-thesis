#include "debug/debug_helpers.h"

#include "utilities/file_helper.h"

#include <nox/graphics/image.h>

#include <stb_image.h>

namespace NOX {

    Image2D::Image2D(std::string_view path) {
        const auto absolutePath = FileHelper::getAbsolutePath(path);
        int32_t width, height, channels;
        if (stbi_is_hdr(absolutePath.c_str())) {
            channels = 4;
            m_data = stbi_loadf(absolutePath.c_str(), &width, &height, nullptr, channels);
        } else {
            m_data = stbi_load(absolutePath.c_str(), &width, &height, &channels, 0);
        }
        NOX_ASSERT_IF((m_data.index() == 0) ? !std::get<0>(m_data) : !std::get<1>(m_data), "Cannot load {0}", path);

        m_width = static_cast<uint32_t>(width);
        m_height = static_cast<uint32_t>(height);
        m_channels = static_cast<uint32_t>(channels);
    }

    Image2D::~Image2D() {
        (m_data.index() == 0) ? stbi_image_free(std::get<0>(m_data)) : stbi_image_free(std::get<1>(m_data));
    }

    template <>
    std::vector<uint8_t> Image2D::getData() const {
        return {std::get<0>(m_data), std::get<0>(m_data) + (m_width * m_height * m_channels)};
    }

    template <>
    std::vector<uint32_t> Image2D::getData() const {
        const auto dataPointer = std::get<0>(m_data);
        std::vector<uint32_t> data;
        data.resize(m_width * m_height);
        for (uint32_t y = 0u; y < m_height; y++) {
            for (uint32_t x = 0u; x < m_width; x++) {
                uint32_t pixelIndex = (y * m_width + x) * m_channels;
                uint32_t r = std::get<0>(m_data)[pixelIndex];
                uint32_t g = m_channels > 1u ? std::get<0>(m_data)[pixelIndex + 1u] : 0u;
                uint32_t b = m_channels > 2u ? std::get<0>(m_data)[pixelIndex + 2u] : 0u;
                uint32_t a = m_channels > 3u ? std::get<0>(m_data)[pixelIndex + 3u] : 0u;
                uint32_t pixelValue = (r << 0u) | (g << 8u) | (b << 16u) | (a << 24u);
                data[y * m_width + x] = pixelValue;
            }
        }

        return data;
    }

    template <>
    std::vector<float> Image2D::getData() const {
        return {std::get<1>(m_data), std::get<1>(m_data) + (m_width * m_height * m_channels)};
    }

} // namespace NOX
