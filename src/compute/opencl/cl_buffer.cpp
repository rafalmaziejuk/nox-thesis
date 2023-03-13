#include "compute/opencl/cl_buffer.h"
#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_helper.h"

#include "utilities/logger.h"

#include <CL/cl.h>

namespace NOX {

    CLBuffer::CLBuffer(const CLContext &context, const uint32_t usage, const size_t size, const void *data) {
        if (size > 0) {
            cl_int result = CL_SUCCESS;
            m_handle = clCreateBuffer(context.getHandle(), static_cast<cl_mem_flags>(usage), size, (void *)data, &result);
            CL_CHECK_STATUS(result);
        } else {
            NOX_DEBUG_LOG(WARN, "Creating NULL buffer");
        }
    }

    CLBuffer::~CLBuffer() {
        if (m_handle) {
            CL_CHECK_STATUS(clReleaseMemObject(static_cast<cl_mem>(m_handle)));
        }
    }

} // namespace NOX
