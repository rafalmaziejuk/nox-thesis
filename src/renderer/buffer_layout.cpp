#include "debug/debug_helpers.h"

#include <nox/renderer/buffer_layout.h>

namespace NOX {

    uint8_t BufferElement::getCountFromType(ElementDataType type) {
        switch (type) {
        case ElementDataType::FLOAT:
            return 1u;

        case ElementDataType::FLOAT2:
            return 2u;

        case ElementDataType::FLOAT3:
            return 3u;

        case ElementDataType::FLOAT4:
            return 4u;

        default:
            NOX_ASSERT_IF(true);
            return 0u;
        }
    }

    uint32_t BufferElement::getSizeFromType(ElementDataType type) {
        switch (type) {
        case ElementDataType::FLOAT:
        case ElementDataType::FLOAT2:
        case ElementDataType::FLOAT3:
        case ElementDataType::FLOAT4:
            return getCountFromType(type) * sizeof(float);

        default:
            NOX_ASSERT_IF(true);
            return 0u;
        }
    }

    void BufferLayout::push(std::string_view name, ElementDataType type, bool normalized) {
        BufferElement element{};
        element.name = name;
        element.type = type;
        element.index = static_cast<uint32_t>(m_elements.size());
        element.dataCount = BufferElement::getCountFromType(type);
        element.normalized = normalized;
        element.offset = m_stride;

        m_stride += BufferElement::getSizeFromType(type);
        m_elements.emplace_back(element);
    }

} // namespace NOX
