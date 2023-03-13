#pragma once

#include <nox/input_identifiers.h>

namespace NOX {

    class Input {
      public:
        static CursorPosition getCursorPosition();
        static bool isMouseButtonPressed(MouseButton button);
        static bool isKeyPressed(Key key);
    };

} // namespace NOX
