#pragma once

typedef struct _cl_device_id *cl_device_id;

namespace NOX {

    class CLPlatform;

    class CLDevice {
      public:
        explicit CLDevice(const CLPlatform &platform);

        cl_device_id getHandle() const { return m_handle; }

      private:
        cl_device_id m_handle{nullptr};
    };

} // namespace NOX
