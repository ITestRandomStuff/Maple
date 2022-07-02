#pragma once

#include <spdlog/spdlog.h>

namespace Maple
{
    class Logger
    {
    public:
        static void Init();

        template<typename... Args>
        static inline void Trace(Args&&... args) { s_Logger->trace(std::forward<Args>(args)...); }

        template<typename... Args>
        static inline void Info(Args&&... args) { s_Logger->info(std::forward<Args>(args)...); }

        template<typename... Args>
        static inline void Warn(Args&&... args) { s_Logger->warn(std::forward<Args>(args)...); }

        template<typename... Args>
        static inline void Error(Args&&... args) { s_Logger->error(std::forward<Args>(args)...); }

        template<typename... Args>
        static inline void Crit(Args&&... args) { s_Logger->critical(std::forward<Args>(args)...); }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#if defined(MPL_CONFIG_DEBUG)

#define MPL_LOGGER_INIT() ::Maple::Logger::Init()

#define MPL_LOG(...)      ::Maple::Logger::Trace(__VA_ARGS__)
#define MPL_INFO(...)     ::Maple::Logger::Info(__VA_ARGS__)
#define MPL_WARN(...)     ::Maple::Logger::Warn(__VA_ARGS__)
#define MPL_ERROR(...)    ::Maple::Logger::Error(__VA_ARGS__)
#define MPL_CRIT(...)     ::Maple::Logger::Crit(__VA_ARGS__); throw

#define MPL_ASSERT(condition, ...)          if (!condition) MPL_ERROR(__VA_ARGS__)
#define MPL_CRIT_ASSERT(condition, ...)     if (!condition) { MPL_CRIT(__VA_ARGS__); }

#else

#define MPL_LOGGER_INIT()

#define MPL_LOG(...)
#define MPL_INFO(...)
#define MPL_WARN(...)
#define MPL_ERROR(...)
#define MPL_CRIT(...)

#define MPL_ASSERT(condition, ...)
#define MPL_CRIT_ASSERT(condition, ...)

#endif