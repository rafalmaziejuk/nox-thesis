#include "debug/debug_helpers.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

namespace NOX {

    void DebugHelper::debugBreak(int line, const char *file) {
        printf("Assert was called at %d line in file:\n%s\n", line, file);
        fflush(stdout);
        assert(false);
    }

    void DebugHelper::abortUnrecoverable(int line, const char *file) {
        printf("Abort was called at %d line in file:\n%s\n", line, file);
        fflush(stdout);
        abort();
    }

} // namespace NOX
