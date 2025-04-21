/******************************************************************************
 *  @file       Telnet.hpp
 *  @brief      Implements Telnet service using Linux socket
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

#ifndef _TELNET_HPP_
#define _TELNET_HPP_

#include "TelnetIf.hpp"
#include "ServiceIf.hpp"
#include "NoCopy.hpp"

class Telnet : public TelnetIf, public ServiceIf, private NoCopy {
public:
    static Telnet& getInstance() {
        static Telnet instance;
        return instance;
    }

    int readNoBlock() override;
    int readBlocked() override;

private:
    Telnet() = default;
    ~Telnet() = default;
};

#endif  // _TELNET_HPP_
