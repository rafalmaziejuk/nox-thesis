#include "compute/opencl/cl_buffer.h"
#include "compute/opencl/cl_compute.h"
#include "compute/opencl/cl_image.h"
#include "compute/opencl/cl_program.h"

#include <nox/compute/compute_program.h>

namespace NOX {

    CLCompute::CLCompute() : m_context(),
                             m_commandQueue(m_context) {}

    std::shared_ptr<ComputeImage> CLCompute::createImage(const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data) {
        return std::make_shared<CLImage>(m_context, usage, dataType, image, data);
    }

    std::shared_ptr<ComputeImage> CLCompute::createImage(const uint32_t usage, const Texture &texture) {
        return std::make_shared<CLImage>(m_context, usage, texture);
    }

    std::shared_ptr<ComputeBuffer> CLCompute::createBuffer(const uint32_t usage, const size_t size, const void *data) {
        return std::make_shared<CLBuffer>(m_context, usage, size, data);
    }

    std::shared_ptr<ComputeProgram> CLCompute::createProgram(std::string_view path) {
        return std::make_shared<CLProgram>(m_context, path);
    }

    void CLCompute::enqueueAcquireGLObject(const ComputeObject &object) {
        m_commandQueue.enqueueAcquireGLObject(object);
    }

    void CLCompute::enqueueReleaseGLObject(const ComputeObject &object) {
        m_commandQueue.enqueueReleaseGLObject(object);
    }

    void CLCompute::enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize) {
        m_commandQueue.enqueueNDRangeKernel(kernel, workDimensions, globalWorkSize, localWorkSize);
    }

    void CLCompute::enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize) {
        m_commandQueue.enqueueFillBuffer(buffer, pattern, patternSize, bufferSize);
    }

    void CLCompute::enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size) {
        m_commandQueue.enqueueWriteBuffer(buffer, data, size);
    }

    void CLCompute::flush() {
        m_commandQueue.flush();
    }

    void CLCompute::finish() {
        m_commandQueue.finish();
    }

} // namespace NOX
