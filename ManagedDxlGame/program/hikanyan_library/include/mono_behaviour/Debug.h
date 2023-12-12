#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include <format>

class Debug
{
public:
    // 可変引数テンプレートを使用したメッセージログ
    template <typename... Args>
    static void log(const std::string& format, Args... args)
    {
        const std::string message = std::vformat(format, std::make_format_args(args...));
        log_message(message);
    }

    template <typename... Args>
    static void log_warning(const std::string& format, Args... args)
    {
        const std::string message = std::vformat("Warning: " + format, std::make_format_args(args...));
        log_message(message);
    }

    // エラーログも同様に更新
    template <typename... Args>
    static void log_error(const std::string& format, Args... args)
    {
        const std::string message = std::vformat("Error: " + format, std::make_format_args(args...));
        log_message(message, true);
    }

private:
    static std::mutex mutex_;

    // メッセージの出力を担当するプライベートメソッド
    static void log_message(const std::string& message, bool is_error = false)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_error)
        {
            std::cerr << message << std::endl;
        }
        else
        {
            std::cout << message << std::endl;
        }
    }
};
