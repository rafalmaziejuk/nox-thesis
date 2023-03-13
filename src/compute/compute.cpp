#include "debug/debug_helpers.h"

#include "compute/compute_api.h"
#include "compute/opencl/cl_compute.h"

#include <nox/compute/compute.h>

namespace NOX {

    std::unique_ptr<ComputeAPI> Compute::s_computeApi = nullptr;

    void Compute::initialize() {
        NOX_ABORT_IF(s_computeApi != nullptr);

        switch (ComputeAPI::getComputeApi()) {
        case ComputeAPI::API::OPENCL:
            s_computeApi = std::make_unique<CLCompute>();
            break;

        default:
            NOX_ASSERT_IF(true, "This compute API is not supported");
            break;
        }
    }

    std::shared_ptr<ComputeImage> Compute::createImage(const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data) {
        return s_computeApi->createImage(usage, dataType, image, data);
    }

    std::shared_ptr<ComputeImage> Compute::createImage(const uint32_t usage, const Texture &texture) {
        return s_computeApi->createImage(usage, texture);
    }

    std::shared_ptr<ComputeBuffer> Compute::createBuffer(const uint32_t usage, const size_t size, const void *data) {
        return s_computeApi->createBuffer(usage, size, data);
    }

    std::shared_ptr<ComputeProgram> Compute::createProgram(std::string_view path) {
        return s_computeApi->createProgram(path);
    }

    void Compute::enqueueAcquireGLObject(const ComputeObject &object) {
        s_computeApi->enqueueAcquireGLObject(object);
    }

    void Compute::enqueueReleaseGLObject(const ComputeObject &object) {
        s_computeApi->enqueueReleaseGLObject(object);
    }

    void Compute::enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize) {
        s_computeApi->enqueueNDRangeKernel(kernel, workDimensions, globalWorkSize, localWorkSize);
    }

    void Compute::enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize) {
        s_computeApi->enqueueFillBuffer(buffer, pattern, patternSize, bufferSize);
    }

    void Compute::enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size) {
        s_computeApi->enqueueWriteBuffer(buffer, data, size);
    }

    void Compute::flush() {
        s_computeApi->flush();
    }

    void Compute::finish() {
        s_computeApi->finish();
    }

} // namespace NOX
