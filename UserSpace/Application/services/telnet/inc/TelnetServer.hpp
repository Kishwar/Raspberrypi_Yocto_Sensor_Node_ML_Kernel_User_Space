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
#include "ServiceIf.hpp"
#include "NoCopy.hpp"

#include <atomic>
#include <thread>

class TelnetServer : public TelnetServerIf, public ServiceIf, private NoCopy {
public:
    static TelnetServer& getInstance() {
        static TelnetServer instance;
        return instance;
    }

    ssize_t writeData(const std::string& data) override;
    std::string readData(size_t maxLength = 1024) override;

private:
    TelnetServer();
    ~TelnetServer();

    void setupServer();
    void acceptAndHandleClient();
    void handleClient(int fd);
    void closeSockets();

    static constexpr uint16_t PORT = 23;
    int server_fd;
    std::atomic<int> client_fd;
    std::thread client_thread;         // this will be replaced
};

#endif  // _TELNET_SERVER_HPP_
