#include <nox/application.h>
#include <nox/input.h>
#include <nox/window.h>

namespace NOX {

    CursorPosition Input::getCursorPosition() {
        const auto &window = Application::get()->getWindow();
        return window.getCursorPosition();
    }

    bool Input::isMouseButtonPressed(MouseButton button) {
        const auto &window = Application::get()->getWindow();
        return window.isMouseButtonPressed(button);
    }

    bool Input::isKeyPressed(Key key) {
        const auto &window = Application::get()->getWindow();
        return window.isKeyPressed(key);
    }

} // namespace NOX
