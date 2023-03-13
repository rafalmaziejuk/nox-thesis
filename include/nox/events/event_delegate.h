#pragma once

#include <functional>
#include <vector>

namespace NOX {

    template <typename... Args>
    class EventDelegate {
      public:
        void subscribe(std::function<void(Args &&...)> handler) {
            m_handlers.emplace_back(handler);
        }

        void fire(Args &&...args) const {
            for (const auto &handler : m_handlers) {
                handler(std::forward<Args>(args)...);
            }
        }

      private:
        std::vector<std::function<void(Args &&...)>> m_handlers;
    };

} // namespace NOX
