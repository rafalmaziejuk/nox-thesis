#pragma once

#include <nox/common_types.h>

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace NOX {

    struct BufferElement {
        static uint8_t getCountFromType(ElementDataType type);
        static uint32_t getSizeFromType(ElementDataType type);

        std::string name;
        ElementDataType type;
        uint32_t index{0};
        uint8_t dataCount{0u};
        bool normalized{0u};
        uint32_t offset{0u};
    };

    class BufferLayout {
      public:
        uint32_t getStride() const { return m_stride; }

        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

        void push(std::string_view name, ElementDataType type, bool normalized = false);

      private:
        uint32_t m_stride{0u};
        std::vector<BufferElement> m_elements;
    };

} // namespace NOX
