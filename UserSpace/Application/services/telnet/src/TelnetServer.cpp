/******************************************************************************
 *  @file       TelnetServer.cpp
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

#include "TelnetServer.hpp"

#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>

TelnetServer::TelnetServer(uint16_t port) : mPort_(port), mServerFd_(-1), mClientFd_(-1) {
    setupServer();
    minor_ =  std::make_unique<Thread>(&TelnetServer::acceptAndHandleClient, 10        /** \todo replace magic number */,
                                                                             8 * 1024  /** \todo replace magic number */,
                                                                             Thread::Policy::FIFO,
                                                                             Thread::State::DETACH,
                                                                             this);
    minor_->start();
}

TelnetServer::~TelnetServer() {
    closeSockets();
}

void TelnetServer::setupServer() {
    mServerFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (mServerFd_ < 0) throw std::runtime_error("Socket creation failed");

    int opt = 1;
    setsockopt(mServerFd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(mPort_);

    if (bind(mServerFd_, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Bind failed");

    if (listen(mServerFd_, 1) < 0)
        throw std::runtime_error("Listen failed");
}

void TelnetServer::acceptAndHandleClient() {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    mClientFd_ = accept(mServerFd_, (sockaddr*)&client_addr, &client_len);
    if (mClientFd_ < 0) {
        throw std::runtime_error("Accept failed");
        return;
    }

    write_ = std::make_unique<Thread>([this]() {
                                        this->write();
                                      },
                                      10,       /** \todo replace magic number */
                                      8 * 1024, /** \todo replace magic number */
                                      Thread::Policy::FIFO,
                                      Thread::State::DETACH);

    read_ = std::make_unique<Thread>([this]() {
                                        this->read();
                                     },
                                     10,       /** \todo replace magic number */
                                     8 * 1024, /** \todo replace magic number */
                                     Thread::Policy::FIFO,
                                     Thread::State::DETACH);

    /* start deligated threads -- drived class implements them */
    write_->start();
    read_->start();
}

void TelnetServer::closeSockets() {
    if (mClientFd_ >= 0) close(mClientFd_);
    if (mServerFd_ >= 0) close(mServerFd_);
}

ssize_t TelnetServer::sockWrite(const std::string& data) {
    if(mClientFd_ > 0)
        return send(mClientFd_, data.c_str(), data.size(), 0);
    else
        return -1;
}

std::string TelnetServer::sockRead(char terminator) {
    std::string input;
    char ch;
    while (true) {
        int n = recv(mClientFd_, &ch, 1, 0);
        unsigned char u = static_cast<unsigned char>(ch);
        if (u == 0xFF) {
            char skip[2];
            recv(mClientFd_, skip, 2, 0);   // Telnet command sequence — skip next 2 bytes
            continue;
        }
        if (n <= 0) break;                  // error or disconnect

        if (ch == '\r') continue;           // ignore carriage return
        if (ch == terminator) break;        // stop on newline

        input += ch;
    }
    return input;
}
