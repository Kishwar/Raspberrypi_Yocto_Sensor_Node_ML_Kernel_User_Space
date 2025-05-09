/******************************************************************************
 *  @file       LoggingIf.hpp
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

#ifndef _LOGGING_IF_HPP
#define _LOGGING_IF_HPP

#include "ErrorCodes.hpp"

#include <string>
#include <vector>

enum class Level {
    FATAL, ERROR, INFO, DEBUG, MEDIUM, HIGH
};

class LoggingIf {
public:
    virtual void log(const Level level, const std::string& content) = 0;
    virtual Codes setLevel(const std::vector<std::string>& args) = 0;
    virtual Codes getLevel(std::string& data) = 0;
};

#endif  // _LOGGING_IF_HPP
