#pragma once

// This is a snippet you can put at the top of all of your SKSE plugins!

#include <Windows.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

namespace logger = SKSE::log;

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    std::shared_ptr<spdlog::logger> loggerPtr;
    if (IsDebuggerPresent()) {
        auto debugLoggerPtr = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        spdlog::sinks_init_list loggers{std::move(fileLoggerPtr), std::move(debugLoggerPtr)};
        loggerPtr = std::make_shared<spdlog::logger>("log", loggers);
    } else {
        // If no debugger is attached, only log to the file.
        loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    }
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
}

// Then just call SetupLog() in your SKSE plugin initialization
//
// ^---- don't forget to do this or your logs won't work :)
