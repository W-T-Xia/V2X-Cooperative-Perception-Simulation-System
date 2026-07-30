#pragma once
#include <exception>
#include <string>

class SensorException : public std::exception {
public:
    explicit SensorException(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
private:
    std::string msg_;
};

class ConfigException : public std::exception {
public:
    explicit ConfigException(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
private:
    std::string msg_;
};

class FusionException : public std::exception {
public:
    explicit FusionException(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
private:
    std::string msg_;
};