#include "debug/debug_helpers.h"

#include "compute/opencl/cl_helper.h"

#include "utilities/logger.h"

#include <nox/common_types.h>

#include <array>

#define CL_ERROR_TO_CASE(errorName) \
    case errorName:                 \
        return #errorName;

namespace NOX {

    namespace {
        constexpr std::array<const char *, 2> requiredExtensions = {"cl_khr_icd",
                                                                    "cl_khr_gl_sharing"};

        const char *clErrorToString(const cl_int errorCode) {
            switch (errorCode) {
                CL_ERROR_TO_CASE(CL_INVALID_VALUE);

                CL_ERROR_TO_CASE(CL_INVALID_PLATFORM);

                CL_ERROR_TO_CASE(CL_INVALID_DEVICE);
                CL_ERROR_TO_CASE(CL_DEVICE_NOT_FOUND);
                CL_ERROR_TO_CASE(CL_INVALID_DEVICE_TYPE);
                CL_ERROR_TO_CASE(CL_DEVICE_NOT_AVAILABLE);

                CL_ERROR_TO_CASE(CL_INVALID_CONTEXT);

            default:
                return "UNKNOWN ERROR";
            }
        }
    } // namespace

    void CLHelper::clLogError(const cl_int errorCode) {
        if (errorCode != CL_SUCCESS) {
            NOX_DEBUG_LOG(ERROR, "OpenCL error: {0}", clErrorToString(errorCode));
            NOX_ABORT_IF(true);
        }
    }

    bool CLHelper::requiredExtensionsSupported(std::string_view result) {
        for (auto extension : requiredExtensions) {
            if (result.find(extension) == std::string::npos) {
                return false;
            }
        }

        return true;
    }

    std::string CLHelper::queryPlatformInfo(const cl_platform_id platform, const cl_platform_info parameter) {
        size_t length = 0u;
        CL_CHECK_STATUS(clGetPlatformInfo(platform, parameter, 0, nullptr, &length));

        std::string result;
        result.resize(length);
        CL_CHECK_STATUS(clGetPlatformInfo(platform, parameter, length, result.data(), nullptr));

        return result;
    }

    std::string CLHelper::queryDeviceInfo(const cl_device_id device, const cl_device_info parameter) {
        size_t length = 0u;
        CL_CHECK_STATUS(clGetDeviceInfo(device, parameter, 0, nullptr, &length));

        std::string result;
        result.resize(length);
        CL_CHECK_STATUS(clGetDeviceInfo(device, parameter, length, result.data(), nullptr));

        return result;
    }

    cl_channel_type CLHelper::getChannelType(const uint32_t dataType) {
        switch (dataType) {
        case ImageDataType::FLOAT:
            return CL_FLOAT;

        case ImageDataType::UNSIGNED_INT8:
            return CL_UNSIGNED_INT8;
        }

        return 0u;
    }

    cl_channel_order CLHelper::getChannelOrder(const uint32_t channels) {
        switch (channels) {
        case 1u:
            return CL_R;

        case 3u:
            NOX_ASSERT_IF(true, "RGB CLImage not supported");
            return 0u;

        case 4u:
            return CL_RGBA;

        default:
            return 0u;
        }
    }

} // namespace NOX
