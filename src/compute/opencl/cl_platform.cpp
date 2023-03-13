#include "debug/debug_helpers.h"

#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_platform.h"

#include <CL/cl.h>

#include <vector>

namespace NOX {

    CLPlatform::CLPlatform() {
        cl_uint numberOfPlatforms = 0u;
        CL_CHECK_STATUS(clGetPlatformIDs(0, nullptr, &numberOfPlatforms));
        NOX_ABORT_IF(numberOfPlatforms == 0u);

        std::vector<cl_platform_id> platforms(numberOfPlatforms);
        CL_CHECK_STATUS(clGetPlatformIDs(numberOfPlatforms, platforms.data(), nullptr));

        for (const auto &platform : platforms) {
            const auto &result = CLHelper::queryPlatformInfo(platform, CL_PLATFORM_EXTENSIONS);
            if (CLHelper::requiredExtensionsSupported(result)) {
                m_handle = platform;
                break;
            }
        }
        NOX_ABORT_IF(m_handle == nullptr);
    }

} // namespace NOX
