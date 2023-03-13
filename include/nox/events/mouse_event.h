#pragma once

#include <nox/input_identifiers.h>

namespace NOX {

    class MouseButtonEvent {
      public:
        MouseButtonEvent(MouseButton button, Action action) : m_button(button),
                                                              m_action(action) {}

        MouseButton getButton() const { return m_button; }
        Action getAction() const { return m_action; }

      private:
        MouseButton m_button;
        Action m_action;
    };

    class MouseEnteredWindowEvent {};

    class MouseLeftWindowEvent {};

    class MouseMovedEvent {
      public:
        MouseMovedEvent(const float x, const float y) : m_x(x),
                                                        m_y(y) {}

        float getX() const { return m_x; }
        float getY() const { return m_y; }

      private:
        float m_x;
        float m_y;
    };

    class MouseScrolledEvent {
      public:
        MouseScrolledEvent(const float xOffset, const float yOffset) : m_xOffset(xOffset),
                                                                       m_yOffset(yOffset) {}

        float getXOffset() const { return m_xOffset; }
        float getYOffset() const { return m_yOffset; }

      private:
        float m_xOffset;
        float m_yOffset;
    };

} // namespace NOX
