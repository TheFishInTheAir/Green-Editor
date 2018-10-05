#pragma once

#define ge_DEBUG_TIMER_INIT auto __start = std::chrono::system_clock::now(); auto __end = std::chrono::system_clock::now(); std::chrono::duration<double> elapsed_seconds;

#define ge_DEBUG_TIMER_START __start = std::chrono::system_clock::now();
#define ge_DEBUG_TIMER_END(m) __end = std::chrono::system_clock::now(); elapsed_seconds = __end - __start; ge::Log::dbg("DebugTimer", "process name: "+std::string(m)+", elapsed time: " + std::to_string(elapsed_seconds.count()) + "s");
