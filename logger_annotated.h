#pragma once

// Annotated file with comments describing what's going on!

// Include spdlog support for a basic file logger
// See below for more details
#include <spdlog/sinks/basic_file_sink.h>

// Allows us to check if a debugger is attached (optional, see below)
#include <Windows.h>
#include <spdlog/sinks/msvc_sink.h>

// spdlog documentation
// https://github.com/gabime/spdlog

// Allows you to write:
//     logger::info("Hello!");
// Rather than:
//     SKSE::log::info("Hello!");
//
// Also would make it easier to change what 'logger' refers to in the future.
namespace logger = SKSE::log;

// This is where the magic happens:
void SetupLog() {
    // Get the path to the SKSE logs folder
    // This will generally be your Documents\My Games\Skyrim Special Edition\SKSE
    //                          or Documents\My Games\Skyrim Special Edition GOG\SKSE
    auto logsFolder = SKSE::log::log_directory();

    // I really don't understand why the log_directory() might not be provided sometimes,
    // but... just incase... ?
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");

    // Get the name of this SKSE plugin. We will use it to name the log file.
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();

    // Generate a path to our log file
    // e.g. Documents\My Games\Skyrim Special Edition\SKSE\OurPlugin.log
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);

    // Now, use whatever you want, but spdlog comes with CommonLibSSE
    // and is the SKSE logger of choice. So you might as well use it!

    // Let's use a spdlog "basic file sink"
    // So like... just a file logger...
    // But the spdlog interface really wants a Shared Pointer to the "basic file sink"
    // So we'll make one of those!
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);

    // // Ok, but set_default_logger() specifically wants a Shared Pointer to a spdlog::logger
    // // So we'll make one of those!
    std::shared_ptr<spdlog::logger> loggerPtr;

    // Now, this is pretty cool.
    // If you want the logs to show up *inside your IDE* when you are debugging, use this code.
    // Whenever a debugger is attached, the logs are setup with an *additional* "sink" to goto
    // your IDE's debug output window.
    if (IsDebuggerPresent()) {
        auto debugLoggerPtr = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        spdlog::sinks_init_list loggers{std::move(fileLoggerPtr), std::move(debugLoggerPtr)};
        loggerPtr = std::make_shared<spdlog::logger>("log", loggers);
    } else {
        // If no debugger is attached, only log to the file.
        loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    }

    // We'll give it the logger we made above. Yeah, I know, kinda redundant right? Welcome to C++
    spdlog::set_default_logger(std::move(loggerPtr));

    // Yay, let's setup spdlog now!
    // By default, let's print out *everything* including trace messages
    // You might want to do something like #ifdef NDEBUG then use trace, else use info or higher severity.
    spdlog::set_level(spdlog::level::trace);

    // This bit is important. When does spdlog WRITE to the file?
    // Make sure it does it everytime you log a message, otherwise it won't write to the file until the game exits.
    spdlog::flush_on(spdlog::level::trace);
}
