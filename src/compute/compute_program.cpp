#include <nox/compute/compute.h>
#include <nox/compute/compute_program.h>

namespace NOX {

    std::shared_ptr<ComputeProgram> ComputeProgram::create(std::string_view path) {
        return Compute::createProgram(path);
    }

} // namespace NOX
