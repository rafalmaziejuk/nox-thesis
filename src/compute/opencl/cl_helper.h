#pragma once

#include <CL/cl.h>

#include <string_view>

#define CL_CHECK_STATUS(expression) NOX::CLHelper::clLogError(expression);

namespace NOX {

    class CLHelper {
      public:
        static void clLogError(const cl_int errorCode);
        static bool requiredExtensionsSupported(std::string_view result);
        static std::string queryPlatformInfo(const cl_platform_id platform, const cl_platform_info parameter);
        static std::string queryDeviceInfo(const cl_device_id device, const cl_device_info parameter);
        static cl_channel_type getChannelType(const uint32_t dataType);
        static cl_channel_order getChannelOrder(const uint32_t channels);
    };

} // namespace NOX
