#pragma once

#include <cstdint>
#include <memory>

namespace NOX {

    class ElementBuffer {
      public:
        virtual ~ElementBuffer() = default;

        static std::unique_ptr<ElementBuffer> create(const uint32_t *data, const uint32_t size);

        virtual uint32_t getHandle() const = 0;
        virtual uint32_t getCount() const = 0;
    };

} // namespace NOX
