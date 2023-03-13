#pragma once

#include "utilities/logger.h"

#ifndef NOX_ASSERT_IF
#ifdef _DEBUG
#define NOX_ASSERT_IF(expression, ...)                                 \
    if (expression) {                                                  \
        NOX::DebugHelper::debugBreak(__LINE__, __FILE__, __VA_ARGS__); \
    }
#else
#define NOX_ASSERT_IF(expression, ...) (void)0
#endif
#endif

#define NOX_ABORT_IF(expression)                                  \
    if (expression) {                                             \
        NOX::DebugHelper::abortUnrecoverable(__LINE__, __FILE__); \
    }

namespace NOX {

    class DebugHelper {
      public:
        template <typename... Args>
        static void debugBreak(int line, const char *file, Args &&...args) {
            NOX_DEBUG_LOG(ERROR, std::forward<Args>(args)...);
            debugBreak(line, file);
        }

        static void debugBreak(int line, const char *file);
        [[noreturn]] static void abortUnrecoverable(int line, const char *file);
    };

} // namespace NOX
