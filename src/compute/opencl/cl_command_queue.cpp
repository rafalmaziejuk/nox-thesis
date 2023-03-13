#include "compute/opencl/cl_command_queue.h"
#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_helper.h"

#include <nox/compute/compute_buffer.h>
#include <nox/compute/compute_kernel.h>
#include <nox/compute/compute_object.h>

#include <CL/cl.h>
#include <CL/cl_gl.h>

namespace NOX {

    CLCommandQueue::CLCommandQueue(const CLContext &context) {
        cl_int result = CL_SUCCESS;
        const auto &device = context.getDevice();
        m_handle = clCreateCommandQueue(context.getHandle(), device.getHandle(), 0, &result);
        CL_CHECK_STATUS(result);
    }

    CLCommandQueue::~CLCommandQueue() {
        CL_CHECK_STATUS(clReleaseCommandQueue(m_handle));
    }

    void CLCommandQueue::enqueueAcquireGLObject(const ComputeObject &object) {
        const auto handle = static_cast<cl_mem>(object.getHandle());
        CL_CHECK_STATUS(clEnqueueAcquireGLObjects(m_handle, 1, &handle, 0, nullptr, nullptr));
    }

    void CLCommandQueue::enqueueReleaseGLObject(const ComputeObject &object) {
        const auto handle = static_cast<cl_mem>(object.getHandle());
        CL_CHECK_STATUS(clEnqueueReleaseGLObjects(m_handle, 1, &handle, 0, nullptr, nullptr));
    }

    void CLCommandQueue::enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize) {
        CL_CHECK_STATUS(clEnqueueNDRangeKernel(m_handle, static_cast<cl_kernel>(kernel.getHandle()), workDimensions, nullptr, globalWorkSize, localWorkSize, 0, nullptr, nullptr));
    }

    void CLCommandQueue::enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize) {
        CL_CHECK_STATUS(clEnqueueFillBuffer(m_handle, static_cast<cl_mem>(buffer.getHandle()), pattern, patternSize, 0, bufferSize, 0, nullptr, nullptr));
    }

    void CLCommandQueue::enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size) {
        CL_CHECK_STATUS(clEnqueueWriteBuffer(m_handle, static_cast<cl_mem>(buffer.getHandle()), CL_TRUE, 0, size, data, 0, nullptr, nullptr));
    }

    void CLCommandQueue::flush() {
        CL_CHECK_STATUS(clFlush(m_handle));
    }

    void CLCommandQueue::finish() {
        CL_CHECK_STATUS(clFinish(m_handle));
    }

} // namespace NOX
