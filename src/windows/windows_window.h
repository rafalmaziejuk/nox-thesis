#pragma once

#include <nox/window.h>

struct GLFWwindow;

namespace NOX {

    class WindowsWindow : public Window {
      public:
        explicit WindowsWindow(const WindowSpecification &specification);
        ~WindowsWindow() override;

        void *getWindowHandle() const override { return static_cast<void *>(m_handle); }
        uint32_t getWidth() const override { return m_specification.width; }
        uint32_t getHeight() const override { return m_specification.height; }

        void setVSync(const bool value) override;

        bool isMouseButtonPressed(MouseButton button) const override;
        bool isKeyPressed(Key key) const override;
        CursorPosition getCursorPosition() const override;
        void setCursorPosition(const CursorPosition &position) const override;
        void setCursorMode(CursorMode mode) const override;

        void update() override;

      private:
        GLFWwindow *m_handle{nullptr};
        WindowSpecification m_specification;
    };

} // namespace NOX
