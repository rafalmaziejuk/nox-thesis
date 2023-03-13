#pragma once

#include <nox/assets/asset.h>

#include <nox/compute/compute_kernel.h>

namespace NOX {

    class ComputeProgram : public Asset {
      public:
        ~ComputeProgram() override = default;

        static std::shared_ptr<ComputeProgram> create(std::string_view path);

        virtual ComputeKernel &getKernel(std::string_view name) = 0;
        virtual const ComputeKernel &getKernel(std::string_view name) const = 0;
    };

} // namespace NOX
