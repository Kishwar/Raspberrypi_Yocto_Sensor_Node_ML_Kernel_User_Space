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

#include "NoCopy.hpp"

#include <string>

enum class Level {
    FATAL, ERROR, INFO, DEBUG, MEDIUM, HIGH
};

class LoggingIf : private NoCopy {
public:
    virtual void log(const Level level, const std::string& content) = 0;
    virtual void setLevel(const Level level) = 0;
};

#endif  // _LOGGING_IF_HPP
