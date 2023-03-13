#pragma once

#include <nox/input_identifiers.h>

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace NOX {

    struct WindowSpecification {
        WindowSpecification(void *userPointer = nullptr,
                            std::string_view title = "empty",
                            uint32_t width = 1280u,
                            uint32_t height = 720u,
                            bool isVSync = true) : userPointer(userPointer),
                                                   title(title),
                                                   width(width),
                                                   height(height),
                                                   isVSync(isVSync) {}

        void *userPointer;
        std::string title;
        uint32_t width;
        uint32_t height;
        bool isVSync;
    };

    class Window {
      public:
        virtual ~Window() = default;

        [[nodiscard]] static std::unique_ptr<Window> create(const WindowSpecification &specification = WindowSpecification());

        virtual void *getWindowHandle() const = 0;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setVSync(const bool value) = 0;

        virtual bool isMouseButtonPressed(MouseButton button) const = 0;
        virtual bool isKeyPressed(Key key) const = 0;
        virtual CursorPosition getCursorPosition() const = 0;
        virtual void setCursorPosition(const CursorPosition &position) const = 0;
        virtual void setCursorMode(CursorMode mode) const = 0;

        virtual void update() = 0;
    };

} // namespace NOX
