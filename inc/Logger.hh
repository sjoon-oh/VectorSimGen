// 
// Author: Sukjoon Oh

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger {
    std::string m_loggerName;
    spdlog::logger* m_sharedLogger;

public:
    Logger(const char* p_loggerName) noexcept
        : m_loggerName(p_loggerName)
    {
        m_sharedLogger = spdlog::stdout_color_mt(std::string(p_loggerName)).get();
        spdlog::set_pattern("[%n:%^%l%$] %v");
    }

    static Logger& getInstance() noexcept
    {
        static Logger global_logger("Logger");
        return global_logger;
    }

    spdlog::logger* getLogger() noexcept
    {
        return m_sharedLogger;
    }
};

#endif