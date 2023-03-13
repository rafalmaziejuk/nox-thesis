#pragma once

namespace NOX {

    class ComputeObject {
      public:
        virtual ~ComputeObject() = default;

        void *getHandle() const { return m_handle; }

      protected:
        void *m_handle{nullptr};
    };

} // namespace NOX
