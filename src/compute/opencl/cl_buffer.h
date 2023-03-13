#pragma once

#include <nox/compute/compute_buffer.h>

#include <cstdint>

namespace NOX {

    class CLContext;

    class CLBuffer : public ComputeBuffer {
      public:
        CLBuffer(const CLContext &context, const uint32_t usage, const size_t size, const void *data);
        ~CLBuffer() override;
    };

} // namespace NOX
