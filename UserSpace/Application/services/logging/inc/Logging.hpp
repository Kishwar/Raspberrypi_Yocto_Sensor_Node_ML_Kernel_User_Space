/******************************************************************************
 *  @file       Logging.hpp
 *  @brief      Implements Logging service runs over telnet
 *
 *  @copyright  Copyright (c) 2025 Kishwar Kumar
 *              All rights reserved.
 *
 *  @license    This project is publicly available on GitHub for viewing and
 *              educational/reference purposes only. Redistribution, modification,
 *              or commercial use of any portion of this code is strictly
 *              prohibited without prior written permission from the author.
 *
 *  @author     Kishwar Kumar
 *  @version    1.0
 *
 *  @note       This code is not open source. Unauthorized use is not permitted.
 ******************************************************************************/

#ifndef _LOGGING_HPP
#define _LOGGING_HPP

#include "LoggingIf.hpp"
#include "TelnetServer.hpp"
#include "Queue.hpp"

#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <memory>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

class Logging : public LoggingIf, private TelnetServer {
public:

    static Logging& getInstance() {
        static Logging instance;
        return instance;
    }

    Logging();
    ~Logging() = default;

    void log(const Level level, const std::string& content) override;
    void setLevel(const Level level) override;

    void write() override;
    void read() override;

private:
    Level level_;
    std::unique_ptr<Queue<std::string>> queue_;
    static constexpr uint16_t PORT = 24;
};

#define __DATETIME__ ([]() -> std::string {                            \
    auto now = std::chrono::system_clock::now();                       \
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);     \
    std::ostringstream os;                                             \
    os << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");  \
    return os.str();                                                   \
}())

#define PRINTLOG(level, message)                   \
    do {                                           \
        Logging& logging = Logging::getInstance(); \
        std::ostringstream oss;                    \
        oss << std::left                           \
            << std::setw(20) << __DATETIME__       \
            << std::setw(40) << __FILENAME__       \
            << std::setw(20) << __func__           \
            << std::setw(10)  << __LINE__          \
            << message;                            \
        logging.log(level, oss.str());             \
    } while (0)

#endif  // _LOGGING_HPP
