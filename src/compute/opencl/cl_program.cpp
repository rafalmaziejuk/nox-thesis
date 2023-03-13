#include "debug/debug_helpers.h"

#include "compute/opencl/cl_context.h"
#include "compute/opencl/cl_helper.h"
#include "compute/opencl/cl_kernel.h"
#include "compute/opencl/cl_program.h"

#include "utilities/file_helper.h"
#include "utilities/logger.h"

#include <CL/cl.h>

namespace NOX {

    namespace {

        std::string queryKernelFunctionName(const cl_kernel kernel) {
            size_t length = 0u;
            CL_CHECK_STATUS(clGetKernelInfo(kernel, CL_KERNEL_FUNCTION_NAME, 0, nullptr, &length));

            std::string result;
            result.resize(length);
            CL_CHECK_STATUS(clGetKernelInfo(kernel, CL_KERNEL_FUNCTION_NAME, length, result.data(), nullptr));

            result.erase(result.end() - 1);
            return result;
        }

    } // namespace

    CLProgram::CLProgram(const CLContext &context, std::string_view path) : m_context(context.getHandle()),
                                                                            m_device(context.getDevice().getHandle()) {
        m_isReloadable = true;
        m_path = FileHelper::getAbsolutePath(path);

        createProgram();
    }

    CLProgram::~CLProgram() {
        CL_CHECK_STATUS(clReleaseProgram(m_handle));
    }

    void CLProgram::createProgram() {
        auto source = FileHelper::readFile(m_path);
        auto strings = source.c_str();
        auto lenghts = source.size();
        cl_int result = CL_SUCCESS;
        m_handle = clCreateProgramWithSource(m_context, 1, &strings, &lenghts, &result);
        CL_CHECK_STATUS(result);

        const auto options = "-cl-std=CL2.0 -Werror -I " + FileHelper::getParentPath(m_path);
        result = clBuildProgram(m_handle, 1, &m_device, options.c_str(), nullptr, nullptr);
        if (result != CL_SUCCESS) {
            size_t length = 0u;
            CL_CHECK_STATUS(clGetProgramBuildInfo(m_handle, m_device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &length));

            std::string buildLog;
            buildLog.resize(length);
            CL_CHECK_STATUS(clGetProgramBuildInfo(m_handle, m_device, CL_PROGRAM_BUILD_LOG, length, buildLog.data(), nullptr));

            NOX_ASSERT_IF(true, "\"{0}\" program compilation error\n{1}", m_path, buildLog);
        }

        cl_uint numberOfKernels = 0u;
        CL_CHECK_STATUS(clCreateKernelsInProgram(m_handle, 0, nullptr, &numberOfKernels));
        NOX_ABORT_IF(numberOfKernels == 0u);

        m_kernels.reserve(numberOfKernels);
        std::vector<cl_kernel> kernels(numberOfKernels);
        CL_CHECK_STATUS(clCreateKernelsInProgram(m_handle, numberOfKernels, kernels.data(), nullptr));
        for (const auto &kernel : kernels) {
            auto kernelName = queryKernelFunctionName(kernel);
            m_kernels.emplace(kernelName, kernel);
            NOX_DEBUG_LOG(TRACE, "\"{0}\" CL kernel created successfully", kernelName);
        }

        NOX_DEBUG_LOG(TRACE, "\"{0}\" CL program created successfully", m_path);
    }

    void CLProgram::reload() {
        m_kernels.clear();
        CL_CHECK_STATUS(clReleaseProgram(m_handle));
        createProgram();
    }

    ComputeKernel &CLProgram::getKernel(std::string_view name) {
        auto &kernel = m_kernels.find(name.data());
        NOX_ASSERT_IF(kernel == m_kernels.end(), "\"{0}\" kernel not found", name);
        return kernel->second;
    }

    const ComputeKernel &CLProgram::getKernel(std::string_view name) const {
        const auto &kernel = m_kernels.find(name.data());
        NOX_ASSERT_IF(kernel == m_kernels.end(), "\"{0}\" kernel not found", name);
        return kernel->second;
    }

} // namespace NOX
