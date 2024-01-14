#pragma once

#include <memory>
#include "spdlog/spdlog.h"

class Log
{
    static std::shared_ptr<spdlog::logger> s_Logger;
    
public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
};

#define LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_FATAL(...) ::Log::GetLogger()->fatal(__VA_ARGS__)
