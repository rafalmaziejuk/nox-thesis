#include "debug/debug_helpers.h"

#include "compute/opencl/cl_device.h"
#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_platform.h"

#include <CL/cl.h>

#include <vector>

namespace NOX {

    CLDevice::CLDevice(const CLPlatform &platform) {
        cl_uint numberOfDevices = 0u;
        CL_CHECK_STATUS(clGetDeviceIDs(platform.getHandle(), CL_DEVICE_TYPE_GPU, 0, nullptr, &numberOfDevices));
        NOX_ABORT_IF(numberOfDevices == 0u);

        std::vector<cl_device_id> devices(numberOfDevices);
        CL_CHECK_STATUS(clGetDeviceIDs(platform.getHandle(), CL_DEVICE_TYPE_GPU, numberOfDevices, devices.data(), nullptr));

        for (const auto &device : devices) {
            const auto &result = CLHelper::queryDeviceInfo(device, CL_DEVICE_EXTENSIONS);
            if (CLHelper::requiredExtensionsSupported(result)) {
                m_handle = device;
                break;
            }
        }
        NOX_ABORT_IF(m_handle == nullptr);
    }

} // namespace NOX
