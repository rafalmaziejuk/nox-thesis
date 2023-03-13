#pragma once

typedef struct _cl_platform_id *cl_platform_id;

namespace NOX {

    class CLPlatform {
      public:
        CLPlatform();

        cl_platform_id getHandle() const { return m_handle; }

      private:
        cl_platform_id m_handle{nullptr};
    };

} // namespace NOX
