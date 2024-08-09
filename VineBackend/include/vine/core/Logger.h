#pragma once

#include <vine/util/Singleton.h>
#include <vine/core/Base.h>

#include <spdlog/spdlog.h>
#include <memory>

namespace vine
{
    class Logger : public Singleton<Logger>
    {
        friend class Singleton<Logger>;
    public:
        ~Logger();

        std::shared_ptr<spdlog::logger>& getLogger() { return logger_; }

        static void init();
        static void shutdown();

    private:
        Logger();

        std::shared_ptr<spdlog::logger> logger_;
    };
}

#define DBG_INFO(...)   SPDLOG_LOGGER_INFO(vine::Logger::ref().getLogger(), __VA_ARGS__)
#define DBG_WARN(...)   SPDLOG_LOGGER_WARN(vine::Logger::ref().getLogger(), __VA_ARGS__)
#define DBG_ERROR(...)  SPDLOG_LOGGER_ERROR(vine::Logger::ref().getLogger(), __VA_ARGS__)
#define DBG_CRIT(...)   SPDLOG_LOGGER_CRITICAL(vine::Logger::ref().getLogger(), __VA_ARGS__)

#define DBG_ASSERT(cond, ...) if ((cond)) {} else { DBG_CRIT(__VA_ARGS__); }