#pragma once

#include <cstdint>

typedef struct _cl_command_queue *cl_command_queue;

namespace NOX {

    class CLContext;
    class ComputeBuffer;
    class ComputeKernel;
    class ComputeObject;

    class CLCommandQueue {
      public:
        explicit CLCommandQueue(const CLContext &context);
        ~CLCommandQueue();

        cl_command_queue getHandle() const { return m_handle; }

        void flush();
        void finish();

        void enqueueAcquireGLObject(const ComputeObject &object);
        void enqueueReleaseGLObject(const ComputeObject &object);
        void enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize);

        void enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize);
        void enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size);

      private:
        cl_command_queue m_handle{nullptr};
    };

} // namespace NOX
