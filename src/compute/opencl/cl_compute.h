#pragma once

#include "compute/compute_api.h"
#include "compute/opencl/cl_command_queue.h"
#include "compute/opencl/cl_context.h"

namespace NOX {

    class CLCompute : public ComputeAPI {
      public:
        CLCompute();
        ~CLCompute() override = default;

        void flush() override;
        void finish() override;

        std::shared_ptr<ComputeBuffer> createBuffer(uint32_t usage, size_t size, const void *data) override;
        std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data) override;
        std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const Texture &texture) override;
        std::shared_ptr<ComputeProgram> createProgram(std::string_view path) override;

        void enqueueAcquireGLObject(const ComputeObject &object) override;
        void enqueueReleaseGLObject(const ComputeObject &object) override;
        void enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize) override;

        void enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize) override;
        void enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size) override;

      private:
        CLContext m_context;
        CLCommandQueue m_commandQueue;
    };

} // namespace NOX
