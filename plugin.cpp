#include "logger.h"  // <--- you can simply copy logger.h into your projects
                     //      and then call SetupLog() in your SKSE plugin
                     //      and start using logger::info() logger::trace() etc!

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

    // Setup logging (e.g. using spdlog)
    SetupLog();

    // Note: the `spdlog` and `SKSE::log` examples below are for demonstration.
    //       I recommend you always use `logger`, e.g. logger::info()

    // Now log something!
    spdlog::info("Wassup, hi from info!");
    spdlog::error("Oh noes! Something bad with error code {} happened!", 69);

    // Here is what the lines will look like in the log:
    // [2022-12-11 12:52:35.797] [plugin-log] [info] Wassup, hi from info!
    // [2022-12-11 12:52:35.798] [plugin-log] [error] Oh noes! Something bad with error code 69 happened!

    // Cool, cool.
    //
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
