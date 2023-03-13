#pragma once

#include <string_view>
#include <variant>
#include <vector>

namespace NOX {

    class Image2D {
      public:
        Image2D(std::string_view path);
        ~Image2D();

        uint32_t getWidth() const { return m_width; }
        uint32_t getHeight() const { return m_height; }
        uint32_t getChannels() const { return m_channels; }
        size_t getPixelSize() const { return m_channels * ((m_data.index() == 0) ? sizeof(*std::get<0>(m_data)) : sizeof(*std::get<1>(m_data))); }

        template <typename DataType>
        std::vector<DataType> getData() const;

      private:
        uint32_t m_width{0u};
        uint32_t m_height{0u};
        uint32_t m_channels{0u};
        std::variant<uint8_t *, float *> m_data;
    };

} // namespace NOX
