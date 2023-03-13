#pragma once

#include <nox/compute/compute_kernel.h>

typedef struct _cl_kernel *cl_kernel;

namespace NOX {

    class CLKernel : public ComputeKernel {
      public:
        explicit CLKernel(cl_kernel handle);
        ~CLKernel() override;

        void setArg(uint32_t index, const ComputeObject &object) override;
        void setArg(const uint32_t index, const void *data, const size_t size) override;
    };

} // namespace NOX
