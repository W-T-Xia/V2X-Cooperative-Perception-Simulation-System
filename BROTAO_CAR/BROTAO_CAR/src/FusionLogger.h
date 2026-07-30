#pragma once
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel { INFO, WARNING, ERROR };

class FusionLogger {
public:
    static FusionLogger& instance();
    void log(const std::string& msg, LogLevel level = LogLevel::INFO);
    ~FusionLogger();

    FusionLogger(const FusionLogger&) = delete;
    FusionLogger& operator=(const FusionLogger&) = delete;

private:
    FusionLogger();
    std::ofstream log_file_;
    std::mutex mutex_;
};