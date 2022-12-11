// Include spdlog support for a basic file logger
// See below for more details
#include "spdlog/sinks/basic_file_sink.h"

// spdlog documentation
// https://github.com/gabime/spdlog

void SetupLog() {
    // Get the name of this SKSE plugin. We will use it to name the log file.
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();

    // Get the path to the SKSE log directory
    // and specify that the log file will be inside of that folder
    // and named "<plugin name>.log"
    //
    // Note: if you want to be truly accurate, you should check whether or not
    // SKSE::log::log_directory provided a value (it is std::optional) else error.
    // But, whatever.
    auto logFilePath = *SKSE::log::log_directory() / std::format("{}.log", pluginName);

    // Now, use whatever you want, but spdlog comes with CommonLibSSE
    // and is the SKSE logger of choice. So you might as well use it!

    // This first line will set the default spdlog logger to
    // a basic logger using our log file path:
    spdlog::set_default_logger(spdlog::basic_logger_mt("plugin-log", logFilePath.string(), true));
    // ^ "plugin-log" is literally whatever, it's a log name registered by spdlog
    //   and the 'true' tells spdlog to clear the file before starting to write to it
    //   so we don't keep writing more content to a file every time the game runs

    // Now, what is the default log "level" that you want?
    // Maybe you want to #ifdef NDEBUG set this to 'trace' for your Debug builds
    // and set it to 'info' for your Release builds? You do you, my friend.
    // I'm gonna log everything by seting this to 'trace'
    spdlog::set_level(spdlog::level::trace);
}

// Read about this more below...
namespace logger = SKSE::log;

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

    // Setup logging (e.g. using spdlog)
    SetupLog();

    // Now log something!
    spdlog::info("Wassup, hi from info!");
    spdlog::error("Oh noes! Something bad with error code {} happened!", 69);

    // Here is what the lines will look like in the log:
    // [2022-12-11 12:52:35.797] [plugin-log] [info] Wassup, hi from info!
    // [2022-12-11 12:52:35.798] [plugin-log] [error] Oh noes! Something bad with error code 69 happened!

    // Cool, cool.
    // Now if you want to be more SKSE-ish, you should use SKSE::log (which just calls spdlog)
    SKSE::log::info("SKSE log info");
    SKSE::log::error("SKSE log error {}", 123);

    // SKSE::log uses spdlog but it adds a super useful prefix
    // which shows the actual line of code which the log was sent from!
    // Here is what the lines will look like in the log:
    // [2022-12-11 12:52:35.798] [plugin-log] [info] [plugin.cpp:52] SKSE log info
    // [2022-12-11 12:52:35.798] [plugin-log] [error] [plugin.cpp:53] SKSE log error 123
    // [2022-12-11 12:52:35.798] [plugin-log] [trace] [plugin.cpp:58] Logged using a nice shorthand for SKSE::log
    // The [plugin.cpp:<line>] lines are pretty rad, amiright?

    // Maybe, even better, use your own namespace (e.g. by aliasing SKSE::log)
    // And this way you can easily swap our your logger to be whatever you want in the future
    // so long as you provide this same interface.
    logger::trace("Logged using a nice shorthand for SKSE::log");

    // That's all, folks! Happy Modding!

    return true;
}
