#pragma once

#include <functional>
#include <iosfwd>
#include <mutex>
#include <string>

namespace hikanyan {

enum class LogLevel {
    Info,
    Warning,
    Error,
};

class Debug {
public:
    using Sink = std::function<void(LogLevel, const std::string&)>;

    static void set_sink(Sink sink);
    static void reset_sink();

    static void log(const std::string& message);
    static void log_warning(const std::string& message);
    static void log_error(const std::string& message);

private:
    static void write(LogLevel level, const std::string& message);
    static Sink& sink();
    static std::mutex& mutex();
};

} // namespace hikanyan
