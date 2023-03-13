#pragma once

#include <cstdint>

namespace NOX {

    class WindowCloseEvent {};

    class WindowResizeEvent {
      public:
        WindowResizeEvent(const uint32_t width, const uint32_t height) : m_width(width),
                                                                         m_height(height) {}

        uint32_t getWidth() const { return m_width; }
        uint32_t getHeight() const { return m_height; }

      private:
        uint32_t m_width;
        uint32_t m_height;
    };

} // namespace NOX
