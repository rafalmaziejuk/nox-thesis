#include "debug/debug_helpers.h"

#include "renderer/renderer_context.h"

#include "windows/windows_window.h"

#include <nox/application.h>

#include <nox/events/event_dispatcher.h>

#include <GLFW/glfw3.h>

namespace NOX {

    WindowsWindow::WindowsWindow(const WindowSpecification &specification) : m_specification(specification) {
        auto result = glfwInit();
        NOX_ABORT_IF(!result);

        m_handle = glfwCreateWindow(m_specification.width, m_specification.height, m_specification.title.c_str(), nullptr, nullptr);
        NOX_ABORT_IF(m_handle == nullptr);

        glfwMakeContextCurrent(m_handle);
        RendererContext::initialize();

        setVSync(m_specification.isVSync);

        glfwSetWindowUserPointer(m_handle, m_specification.userPointer);

        auto windowCloseCallback = [](GLFWwindow *handle) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            eventDispatcher.getWindowCloseEventDelegate().fire({});
        };
        glfwSetWindowCloseCallback(m_handle, windowCloseCallback);

        auto windowResizeCallback = [](GLFWwindow *handle, int width, int height) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            eventDispatcher.getWindowResizeEventDelegate().fire({static_cast<uint32_t>(width), static_cast<uint32_t>(height)});
        };
        glfwSetWindowSizeCallback(m_handle, windowResizeCallback);

        auto mouseButtonCallback = [](GLFWwindow *handle, int button, int action, int mods) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            auto mouseAction = static_cast<bool>(action) ? Action::PRESSED : Action::RELEASED;
            MouseButton mouseButton{};

            switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                mouseButton = MouseButton::LEFT;
                break;

            case GLFW_MOUSE_BUTTON_RIGHT:
                mouseButton = MouseButton::RIGHT;
                break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
                mouseButton = MouseButton::MIDDLE;
                break;

            case GLFW_MOUSE_BUTTON_4:
                mouseButton = MouseButton::BUTTON_4;
                break;

            case GLFW_MOUSE_BUTTON_5:
                mouseButton = MouseButton::BUTTON_5;
                break;

            case GLFW_MOUSE_BUTTON_6:
                mouseButton = MouseButton::BUTTON_6;
                break;

            case GLFW_MOUSE_BUTTON_7:
                mouseButton = MouseButton::BUTTON_7;
                break;

            case GLFW_MOUSE_BUTTON_8:
                mouseButton = MouseButton::BUTTON_8;
                break;
            }

            eventDispatcher.getMouseButtonEventDelegate().fire({mouseButton, mouseAction});
        };
        glfwSetMouseButtonCallback(m_handle, mouseButtonCallback);

        auto mouseCursorEnterCallback = [](GLFWwindow *handle, int entered) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            if (entered) {
                eventDispatcher.getMouseEnteredWindowEventDelegate().fire({});
            } else {
                eventDispatcher.getMouseLeftWindowEventDelegate().fire({});
            }
        };
        glfwSetCursorEnterCallback(m_handle, mouseCursorEnterCallback);

        auto mouseMovedCallback = [](GLFWwindow *handle, double x, double y) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            eventDispatcher.getMouseMovedEventDelegate().fire({static_cast<float>(x), static_cast<float>(y)});
        };
        glfwSetCursorPosCallback(m_handle, mouseMovedCallback);

        auto mouseScrolledCallback = [](GLFWwindow *handle, double xOffset, double yOffset) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            eventDispatcher.getMouseScrolledEventDelegate().fire({static_cast<float>(xOffset), static_cast<float>(yOffset)});
        };
        glfwSetScrollCallback(m_handle, mouseScrolledCallback);

        auto keyCallback = [](GLFWwindow *handle, int key, int scancode, int action, int mods) {
            auto &eventDispatcher = *(static_cast<EventDispatcher *>(glfwGetWindowUserPointer(handle)));
            auto keyAction = static_cast<bool>(action) ? Action::PRESSED : Action::RELEASED;
            Key keyValue{};

            switch (key) {
            case GLFW_KEY_A:
                keyValue = Key::A;
                break;

            case GLFW_KEY_D:
                keyValue = Key::D;
                break;

            case GLFW_KEY_R:
                keyValue = Key::R;
                break;

            case GLFW_KEY_S:
                keyValue = Key::S;
                break;

            case GLFW_KEY_W:
                keyValue = Key::W;
                break;

            case GLFW_KEY_SPACE:
                keyValue = Key::SPACE;
                break;

            case GLFW_KEY_LEFT_SHIFT:
                keyValue = Key::LSHIFT;
                break;

            case GLFW_KEY_LEFT_CONTROL:
                keyValue = Key::LCTRL;
                break;

            case GLFW_KEY_ESCAPE:
                keyValue = Key::ESCAPE;
                break;
            }

            eventDispatcher.getKeyEventDelegate().fire({keyValue, keyAction});
        };
        glfwSetKeyCallback(m_handle, keyCallback);
    }

    WindowsWindow::~WindowsWindow() {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }

    void WindowsWindow::setVSync(const bool value) {
        glfwSwapInterval(m_specification.isVSync ? 1 : 0);
    }

    CursorPosition WindowsWindow::getCursorPosition() const {
        double x, y;
        glfwGetCursorPos(m_handle, &x, &y);

        return {static_cast<float>(x), static_cast<float>(y)};
    }

    bool WindowsWindow::isMouseButtonPressed(MouseButton button) const {
        uint32_t mouseButton{};
        switch (button) {
        case MouseButton::LEFT:
            mouseButton = GLFW_MOUSE_BUTTON_LEFT;
            break;

        case MouseButton::RIGHT:
            mouseButton = GLFW_MOUSE_BUTTON_RIGHT;
            break;

        case MouseButton::MIDDLE:
            mouseButton = GLFW_MOUSE_BUTTON_MIDDLE;
            break;

        case MouseButton::BUTTON_4:
            mouseButton = GLFW_MOUSE_BUTTON_4;
            break;

        case MouseButton::BUTTON_5:
            mouseButton = GLFW_MOUSE_BUTTON_5;
            break;

        case MouseButton::BUTTON_6:
            mouseButton = GLFW_MOUSE_BUTTON_6;
            break;

        case MouseButton::BUTTON_7:
            mouseButton = GLFW_MOUSE_BUTTON_7;
            break;

        case MouseButton::BUTTON_8:
            mouseButton = GLFW_MOUSE_BUTTON_8;
            break;
        }

        return static_cast<bool>(glfwGetMouseButton(m_handle, mouseButton));
    }

    bool WindowsWindow::isKeyPressed(Key key) const {
        uint32_t keyValue{};
        switch (key) {
        case Key::A:
            keyValue = GLFW_KEY_A;
            break;

        case Key::D:
            keyValue = GLFW_KEY_D;
            break;

        case Key::R:
            keyValue = GLFW_KEY_R;
            break;

        case Key::S:
            keyValue = GLFW_KEY_S;
            break;

        case Key::W:
            keyValue = GLFW_KEY_W;
            break;

        case Key::SPACE:
            keyValue = GLFW_KEY_SPACE;
            break;

        case Key::LSHIFT:
            keyValue = GLFW_KEY_LEFT_SHIFT;
            break;

        case Key::LCTRL:
            keyValue = GLFW_KEY_LEFT_CONTROL;
            break;

        case Key::ESCAPE:
            keyValue = GLFW_KEY_ESCAPE;
            break;
        }

        return static_cast<bool>(glfwGetKey(m_handle, keyValue));
    }

    void WindowsWindow::setCursorMode(CursorMode mode) const {
        int32_t modeValue{};
        switch (mode) {
        case CursorMode::NORMAL:
            modeValue = GLFW_CURSOR_NORMAL;
            break;

        case CursorMode::HIDDEN:
            modeValue = GLFW_CURSOR_HIDDEN;
            break;

        case CursorMode::DISABLED:
            modeValue = GLFW_CURSOR_DISABLED;
            break;
        }

        glfwSetInputMode(m_handle, GLFW_CURSOR, modeValue);
    }

    void WindowsWindow::setCursorPosition(const CursorPosition &position) const {
        glfwSetCursorPos(m_handle, static_cast<double>(position.x), static_cast<double>(position.y));
    }

    void WindowsWindow::update() {
        glfwPollEvents();
        glfwSwapBuffers(m_handle);
    }

} // namespace NOX
