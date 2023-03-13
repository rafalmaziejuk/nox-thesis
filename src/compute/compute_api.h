#pragma once

#include <memory>
#include <string_view>

namespace NOX {

    class ComputeBuffer;
    class ComputeImage;
    class ComputeKernel;
    class ComputeObject;
    class ComputeProgram;
    class Image2D;
    class Texture;

    class ComputeAPI {
      public:
        enum class API {
            OPENCL
        };

      public:
        virtual ~ComputeAPI() = default;

        virtual void flush() = 0;
        virtual void finish() = 0;

        virtual std::shared_ptr<ComputeBuffer> createBuffer(const uint32_t usage, const size_t size, const void *data) = 0;
        virtual std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data) = 0;
        virtual std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const Texture &texture) = 0;
        virtual std::shared_ptr<ComputeProgram> createProgram(std::string_view path) = 0;

        virtual void enqueueAcquireGLObject(const ComputeObject &object) = 0;
        virtual void enqueueReleaseGLObject(const ComputeObject &object) = 0;
        virtual void enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize) = 0;

        virtual void enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize) = 0;
        virtual void enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size) = 0;

        static API getComputeApi() { return s_computeApi; }

      private:
        static API s_computeApi;
    };

} // namespace NOX
