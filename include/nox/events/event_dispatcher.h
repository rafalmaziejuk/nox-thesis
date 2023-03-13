#pragma once

#include <nox/events/event_delegate.h>
#include <nox/events/keyboard_event.h>
#include <nox/events/mouse_event.h>
#include <nox/events/window_event.h>

namespace NOX {

    class EventDispatcher {
        using KeyEventDelegate = EventDelegate<KeyEvent>;

        using MouseButtonEventDelegate = EventDelegate<MouseButtonEvent>;
        using MouseEnteredWindowEventDelegate = EventDelegate<MouseEnteredWindowEvent>;
        using MouseLeftWindowEventDelegate = EventDelegate<MouseLeftWindowEvent>;
        using MouseMovedEventDelegate = EventDelegate<MouseMovedEvent>;
        using MouseScrolledEventDelegate = EventDelegate<MouseScrolledEvent>;

        using WindowCloseEventDelegate = EventDelegate<WindowCloseEvent>;
        using WindowResizeEventDelegate = EventDelegate<WindowResizeEvent>;

      public:
        KeyEventDelegate &getKeyEventDelegate() { return m_keyEventDelegate; }

        MouseButtonEventDelegate &getMouseButtonEventDelegate() { return m_mouseButtonEventDelegate; }
        MouseEnteredWindowEventDelegate &getMouseEnteredWindowEventDelegate() { return m_mouseEnteredWindowEventDelegate; }
        MouseLeftWindowEventDelegate &getMouseLeftWindowEventDelegate() { return m_mouseLeftWindowEventDelegate; }
        MouseMovedEventDelegate &getMouseMovedEventDelegate() { return m_mouseMovedEventDelegate; }
        MouseScrolledEventDelegate &getMouseScrolledEventDelegate() { return m_mouseScrolledEventDelegate; }

        WindowCloseEventDelegate &getWindowCloseEventDelegate() { return m_windowCloseEventDelegate; }
        WindowResizeEventDelegate &getWindowResizeEventDelegate() { return m_windowResizeEventDelegate; }

      private:
        KeyEventDelegate m_keyEventDelegate;

        MouseButtonEventDelegate m_mouseButtonEventDelegate;
        MouseEnteredWindowEventDelegate m_mouseEnteredWindowEventDelegate;
        MouseLeftWindowEventDelegate m_mouseLeftWindowEventDelegate;
        MouseMovedEventDelegate m_mouseMovedEventDelegate;
        MouseScrolledEventDelegate m_mouseScrolledEventDelegate;

        WindowCloseEventDelegate m_windowCloseEventDelegate;
        WindowResizeEventDelegate m_windowResizeEventDelegate;
    };

} // namespace NOX
