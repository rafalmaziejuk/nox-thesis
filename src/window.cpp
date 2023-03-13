#include "debug/debug_helpers.h"

#ifdef NOX_WIN32
#include "windows/windows_window.h"
#endif

#include <nox/window.h>

namespace NOX {

    std::unique_ptr<Window> Window::create(const WindowSpecification &specification) {
#ifdef NOX_WIN32
        return std::make_unique<WindowsWindow>(specification);
#endif

        NOX_ABORT_IF(true);
        return nullptr;
    }

} // namespace NOX
