#include "debug/debug_helpers.h"

#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_platform.h"

#include "utilities/logger.h"

#include <CL/cl.h>
#include <CL/cl_gl.h>

#ifdef NOX_WIN32
#include <Windows.h>
#endif

namespace NOX {

    CLContext::CLContext() : m_platform(),
                             m_device(m_platform) {
        NOX_DEBUG_LOG(INFO, "OpenCL version: {0}", CLHelper::queryPlatformInfo(m_platform.getHandle(), CL_PLATFORM_VERSION));

#ifdef NOX_WIN32
        cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)m_platform.getHandle(),
            0};
#else
        NOX_ABORT_IF(true);
#endif

        cl_int result = CL_SUCCESS;
        m_handle = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, nullptr, nullptr, &result);
        CL_CHECK_STATUS(result);
    }

    CLContext::~CLContext() {
        CL_CHECK_STATUS(clReleaseContext(m_handle));
    }

} // namespace NOX
