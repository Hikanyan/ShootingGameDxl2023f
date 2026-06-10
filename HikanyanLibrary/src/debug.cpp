#include <hikanyan/core/debug.hpp>

#include <iostream>
#include <utility>

namespace hikanyan {

void Debug::set_sink(Sink sink_value) {
    std::lock_guard lock(mutex());
    sink() = std::move(sink_value);
}

void Debug::reset_sink() {
    std::lock_guard lock(mutex());
    sink() = {};
}

void Debug::log(const std::string& message) {
    write(LogLevel::Info, message);
}

void Debug::log_warning(const std::string& message) {
    write(LogLevel::Warning, message);
}

void Debug::log_error(const std::string& message) {
    write(LogLevel::Error, message);
}

void Debug::write(LogLevel level, const std::string& message) {
    std::lock_guard lock(mutex());

    if (sink()) {
        sink()(level, message);
        return;
    }

    switch (level) {
    case LogLevel::Info:
        std::cout << message << '\n';
        break;
    case LogLevel::Warning:
        std::cout << "Warning: " << message << '\n';
        break;
    case LogLevel::Error:
        std::cerr << "Error: " << message << '\n';
        break;
    }
}

Debug::Sink& Debug::sink() {
    static Sink value;
    return value;
}

std::mutex& Debug::mutex() {
    static std::mutex value;
    return value;
}

} // namespace hikanyan
