#include "Logger.hpp"
#include <stdio.h>

std::mutex Logger::s_log_mutex;
std::ofstream Logger::s_log_file;

void Logger::log(const char* msg, const source_location loc) noexcept {
    std::lock_guard<std::mutex> lock(Logger::s_log_mutex);

    // Zabezpieczenie przed możliwym podaniem wartości
    // nullptr lub NULL jako argument
    if (!msg) {
        msg = "";
    }

    #ifdef DEBUG_MODE
    fprintf(stderr, "file: %s(%u:%u) `%s`: %s.\n", loc.file_name(), loc.line(), loc.column(), loc.function_name(), msg);
    #else
    try {
        if (!Logger::s_log_file.is_open()) {
            Logger::s_log_file.open("log.txt", std::ios::out | std::ios::app);
        }

        Logger::s_log_file 
            << "file: " << loc.file_name() << "(" << loc.line() << ":" << loc.column() << ") " 
            << "`" << loc.function_name() << "`: " << msg << ".\n"; 
    } catch (...) {};
    #endif
}