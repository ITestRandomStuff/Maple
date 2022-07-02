#include "pch.h"
#include "Maple/Debug/Log.h"

#include <spdlog/sinks/ansicolor_sink.h>

namespace Maple
{
    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    void Logger::Init()
    {
        // Create an ansicolor_sink and set the pattern.
        // Ex: [Maple]: Text To Log
        auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>(spdlog::color_mode::always);
        sink->set_pattern("%^[%n]: %v%$");

        // Set the color.
        sink->set_color(spdlog::level::trace,    sink->white);
        sink->set_color(spdlog::level::info,     sink->cyan);

        sink->set_color(spdlog::level::warn,     sink->yellow);
        sink->set_color(spdlog::level::err,      sink->red_bold);
        sink->set_color(spdlog::level::critical, sink->red);

        // Create and register the logger.
        s_Logger = std::make_shared<spdlog::logger>("Maple", sink);
        spdlog::register_logger(s_Logger);

        // Set the global logging level.
        spdlog::set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }
}