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

#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include "LoggingIf.hpp"
#include "TelnetServer.hpp"
#include "Queue.hpp"
#include "Cli.hpp"

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

    void log(const Level level, const std::string& content) override;
    Codes setLevel(const std::vector<std::string>& args) override;
    Codes getLevel(std::string& data) override;

    void write() override;
    void read() override;

private:
    Level level_;
    std::unique_ptr<Queue<std::string>> queue_;
    static constexpr uint16_t PORT = 24;

    Logging();
    ~Logging() = default;
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

/* register CLI command with linkerset */
CLI_COMMAND_REGISTER_BOTH("loglevel", Logging, setLevel, getLevel);

/* register class to be auto-activated at startup (linkerset) */
REGISTER_AUTO_INIT(Logging)

#endif  // _LOGGING_HPP_
