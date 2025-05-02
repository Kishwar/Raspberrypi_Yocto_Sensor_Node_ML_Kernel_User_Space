/******************************************************************************
 *  @file       TelnetServer.hpp
 *  @brief      Implements TelnetServer service using Linux socket
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

#ifndef _TELNET_SERVER_HPP_
#define _TELNET_SERVER_HPP_

#include "TelnetServerIf.hpp"
#include "Thread.hpp"

#include <atomic>
#include <memory>

class TelnetServer : public TelnetServerIf {
public:
    TelnetServer(uint16_t port);
    virtual ~TelnetServer();

    ssize_t sockWrite(const std::string& data) override;
    std::string sockRead(char terminator) override;

private:
    void setupServer();
    void acceptAndHandleClient();
    void closeSockets();

    uint16_t mPort_;
    int mServerFd_;
    std::atomic<int> mClientFd_;
    std::unique_ptr<Thread> minor_;
    std::unique_ptr<Thread> write_;
    std::unique_ptr<Thread> read_;
};

#endif  // _TELNET_SERVER_HPP_
