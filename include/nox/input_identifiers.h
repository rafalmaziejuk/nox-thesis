#pragma once

namespace NOX {

    struct CursorPosition {
        float x;
        float y;
    };

    enum class CursorMode {
        NORMAL,
        HIDDEN,
        DISABLED
    };

    enum class Action {
        PRESSED,
        RELEASED
    };

    enum class MouseButton {
        LEFT,
        RIGHT,
        MIDDLE,
        BUTTON_4,
        BUTTON_5,
        BUTTON_6,
        BUTTON_7,
        BUTTON_8
    };

    enum class Key {
        NONE,
        A,
        D,
        R,
        S,
        W,
        SPACE,
        LSHIFT,
        LCTRL,
        ESCAPE
    };

} // namespace NOX
