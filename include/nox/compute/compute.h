#pragma once

#include <memory>
#include <string_view>

namespace NOX {

    class ComputeAPI;
    class ComputeBuffer;
    class ComputeImage;
    class ComputeKernel;
    class ComputeObject;
    class ComputeProgram;
    class Image2D;
    class Texture;

    class Compute {
        friend class ComputeProgram;

      public:
        static void initialize();

        static void flush();
        static void finish();

        static std::shared_ptr<ComputeBuffer> createBuffer(const uint32_t usage, const size_t size, const void *data = nullptr);
        static std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data = nullptr);
        static std::shared_ptr<ComputeImage> createImage(const uint32_t usage, const Texture &texture);

        static void enqueueAcquireGLObject(const ComputeObject &object);
        static void enqueueReleaseGLObject(const ComputeObject &object);
        static void enqueueNDRangeKernel(const ComputeKernel &kernel, const uint8_t workDimensions, const size_t *globalWorkSize, const size_t *localWorkSize = nullptr);

        static void enqueueFillBuffer(const ComputeBuffer &buffer, const void *pattern, const size_t patternSize, const size_t bufferSize);
        static void enqueueWriteBuffer(const ComputeBuffer &buffer, const void *data, const size_t size);

      private:
        static std::shared_ptr<ComputeProgram> createProgram(std::string_view path);

      private:
        static std::unique_ptr<ComputeAPI> s_computeApi;
    };

} // namespace NOX
