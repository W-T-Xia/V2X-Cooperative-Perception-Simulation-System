#include "FusionLogger.h"
#include <iostream>
#include <chrono>
#include <ctime>

FusionLogger& FusionLogger::instance() {
    static FusionLogger logger;
    return logger;
}

FusionLogger::FusionLogger() {
    log_file_.open("fusion.log", std::ios::out | std::ios::app);
    if (!log_file_) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

FusionLogger::~FusionLogger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

void FusionLogger::log(const std::string& msg, LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    const char* levelStr = "";
    switch (level) {
    case LogLevel::INFO:    levelStr = "INFO";    break;
    case LogLevel::WARNING: levelStr = "WARNING"; break;
    case LogLevel::ERROR:   levelStr = "ERROR";   break;
    }
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&t);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    if (log_file_.is_open()) {
        log_file_ << "[" << timeStr << "] [" << levelStr << "] " << msg << std::endl;
    }
    // Also output to console
    std::cout << "[" << levelStr << "] " << msg << std::endl;
}