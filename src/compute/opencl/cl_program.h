#pragma once

#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_device.h"
#include "compute/opencl/cl_kernel.h"

#include <nox/compute/compute_program.h>

#include <string>
#include <unordered_map>

typedef struct _cl_program *cl_program;

namespace NOX {

    class CLProgram : public ComputeProgram {
      public:
        CLProgram(const CLContext &context, std::string_view path);
        ~CLProgram();

        void reload() override;

        cl_program getHandle() const { return m_handle; }
        ComputeKernel &getKernel(std::string_view name) override;
        const ComputeKernel &getKernel(std::string_view name) const override;

      private:
        void createProgram();

      private:
        cl_program m_handle{nullptr};
        const cl_context m_context{nullptr};
        const cl_device_id m_device{nullptr};
        std::unordered_map<std::string, CLKernel> m_kernels;
    };

} // namespace NOX
