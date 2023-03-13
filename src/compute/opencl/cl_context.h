#pragma once

#include "compute/opencl/cl_device.h"
#include "compute/opencl/cl_platform.h"

typedef struct _cl_context *cl_context;

namespace NOX {

    class CLContext {
      public:
        CLContext();
        ~CLContext();

        cl_context getHandle() const { return m_handle; }
        const CLDevice &getDevice() const { return m_device; }

      private:
        cl_context m_handle{nullptr};
        CLPlatform m_platform;
        CLDevice m_device;
    };

} // namespace NOX
