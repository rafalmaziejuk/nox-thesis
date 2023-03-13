#pragma once

#include <nox/compute/compute_object.h>

namespace NOX {

    class ComputeBuffer : public ComputeObject {
      public:
        ~ComputeBuffer() override = default;
    };

} // namespace NOX
