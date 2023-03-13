#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_kernel.h"

#include "utilities/logger.h"

#include <nox/compute/compute_object.h>

#include <CL/cl.h>

namespace NOX {

    CLKernel::CLKernel(cl_kernel handle) {
        m_handle = handle;
    }

    CLKernel::~CLKernel() {
        CL_CHECK_STATUS(clReleaseKernel(static_cast<cl_kernel>(m_handle)));
    }

    void CLKernel::setArg(const uint32_t index, const ComputeObject &object) {
        const auto handle = object.getHandle();
        CL_CHECK_STATUS(clSetKernelArg(static_cast<cl_kernel>(m_handle), index, sizeof(cl_mem), &handle));
    }

    void CLKernel::setArg(const uint32_t index, const void *data, const size_t size) {
        CL_CHECK_STATUS(clSetKernelArg(static_cast<cl_kernel>(m_handle), index, size, data));
    }

} // namespace NOX
