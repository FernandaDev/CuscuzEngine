#pragma once

#include "spdlog/spdlog.h"

namespace Cuscuz
{
    class Log
    {
        static std::shared_ptr<spdlog::logger> s_Logger;
    
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
    };

#define LOG_INFO(...) ::Cuscuz::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Cuscuz::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Cuscuz::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_TRACE(...) ::Cuscuz::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_FATAL(...) ::Cuscuz::Log::GetLogger()->fatal(__VA_ARGS__)
}