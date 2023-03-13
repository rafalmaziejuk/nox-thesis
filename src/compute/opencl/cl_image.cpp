#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_image.h"

#include "renderer/opengl/gl_helper.h"

#include <nox/graphics/image.h>

#include <nox/renderer/texture.h>

#include <CL/cl_gl.h>

namespace NOX {

    CLImage::CLImage(const CLContext &context, const uint32_t usage, const uint32_t dataType, const Image2D &image, const void *data) {
        const auto width = image.getWidth();
        const auto height = image.getHeight();
        const auto channels = image.getChannels();

        cl_int result = CL_SUCCESS;
        cl_image_desc description{};
        description.image_type = CL_MEM_OBJECT_IMAGE2D;
        description.image_width = width;
        description.image_height = height;
        description.image_row_pitch = width * image.getPixelSize();

        cl_image_format format;
        format.image_channel_order = CLHelper::getChannelOrder(channels);
        format.image_channel_data_type = CLHelper::getChannelType(dataType);

        m_handle = clCreateImage(context.getHandle(), usage, &format, &description, (void *)data, &result);
        CL_CHECK_STATUS(result);
    }

    CLImage::CLImage(const CLContext &context, const uint32_t usage, const Texture &texture) {
        cl_int result = CL_SUCCESS;
        m_handle = clCreateFromGLTexture(context.getHandle(), usage, GLHelper::getGLTextureType(texture.getType()), 0, texture.getHandle(), &result);
        CL_CHECK_STATUS(result);
    }

    CLImage::~CLImage() {
        if (m_handle) {
            CL_CHECK_STATUS(clReleaseMemObject(static_cast<cl_mem>(m_handle)));
        }
    }

} // namespace NOX
