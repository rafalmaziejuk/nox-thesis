#include "utilities/logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace NOX {

    std::shared_ptr<spdlog::logger> Logger::m_logger;

    void Logger::initialize() {
        std::array<spdlog::sink_ptr, 2> sinks{
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("nox.log")};

        sinks[0]->set_pattern("%^[%T][%l] %v%$");
        sinks[1]->set_pattern("[%T][%l] %v");

        m_logger = std::make_shared<spdlog::logger>("NOX_LOGGER", begin(sinks), end(sinks));
        m_logger->set_level(spdlog::level::trace);
        m_logger->flush_on(spdlog::level::trace);
    }

} // namespace NOX
