#pragma once

#include <spdlog/logger.h>

#define NOX_DEBUG_LOG(logLevel, ...) \
    NOX::Logger::log<NOX::LogLevel::##logLevel>(__VA_ARGS__);

namespace NOX {

    enum class LogLevel : uint8_t {
        TRACE,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    class Logger {
      public:
        static void initialize();

        template <LogLevel logLevel, typename... Args>
        static void log(Args &&...args) {
            switch (logLevel) {
            case LogLevel::TRACE:
                m_logger->trace(std::forward<Args>(args)...);
                break;

            case LogLevel::INFO:
                m_logger->info(std::forward<Args>(args)...);
                break;

            case LogLevel::WARN:
                m_logger->warn(std::forward<Args>(args)...);
                break;

            case LogLevel::ERROR:
                m_logger->error(std::forward<Args>(args)...);
                break;

            case LogLevel::CRITICAL:
                m_logger->critical(std::forward<Args>(args)...);
                break;
            }
        }

      private:
        static std::shared_ptr<spdlog::logger> m_logger;
    };

} // namespace NOX
