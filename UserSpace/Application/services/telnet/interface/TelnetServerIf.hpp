/******************************************************************************
 *  @file       TelnetServerIf.hpp
 *  @brief      Implements Telnet Server service using Linux socket
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

#ifndef _TELNET_SERVER_IF_HPP_
#define _TELNET_SERVER_IF_HPP_

#include <string>

class TelnetServerIf {
public:
    virtual ssize_t sockWrite(const std::string& data) = 0;
    virtual std::string sockRead(char terminator) = 0;

    virtual void write() = 0;
    virtual void read() = 0;
};

#endif  // _TELNET_SERVER_IF_HPP_
