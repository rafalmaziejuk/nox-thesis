#pragma once

#include <nox/compute/compute_object.h>

#include <cstdint>
#include <memory>

namespace NOX {

    class ComputeKernel : public ComputeObject {
      public:
        ~ComputeKernel() override = default;

        virtual void setArg(const uint32_t index, const ComputeObject &object) = 0;
        virtual void setArg(const uint32_t index, const void *data, const size_t size) = 0;
    };

} // namespace NOX
