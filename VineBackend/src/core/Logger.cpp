#include <vine/core/Logger.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace vine
{
    Logger::Logger()
    {
        spdlog::set_pattern("[%10n] [%^%4!l%$] [%-20s:%5#] %v");
        logger_ = spdlog::stdout_color_mt("Vine");
        logger_->set_level(spdlog::level::info);
    }

    Logger::~Logger()
    {
    }

    void Logger::init()
    {
        Logger::createSingleton();
    }

    void Logger::shutdown()
    {
        Logger::destroySingleton();
    }
}