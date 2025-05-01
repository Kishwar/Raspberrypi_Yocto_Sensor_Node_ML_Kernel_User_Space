#include "TelnetServer.hpp"
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
#include <ostream>     // TODO remove this
#include <iostream>    // TODO remove this

TelnetServer::TelnetServer() : server_fd(-1) {
    setupServer();
    client_thread = std::thread(&TelnetServer::acceptAndHandleClient, this);
    client_thread.detach();
}

TelnetServer::~TelnetServer() {
    closeSockets();
}

void TelnetServer::setupServer() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) throw std::runtime_error("Socket creation failed");

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Bind failed");

    if (listen(server_fd, 1) < 0)
        throw std::runtime_error("Listen failed");

    std::cout << "Telnet server listening on port " << PORT << std::endl;        // TODO remove with logging
}

void TelnetServer::acceptAndHandleClient() {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (fd < 0) {
        std::cerr << "Accept failed\n";            // TODO remove with logging
        return;
    }

    std::cout << "Client connected.\n";         // TODO remove with logging
    client_fd = fd;

    std::thread(&TelnetServer::handleClient, this, fd).detach();   // TODO remove with our thread implementation
}

void TelnetServer::handleClient(int fd) {
    const std::string welcome = "Welcome to the Telnet server!\n";
    send(fd, welcome.c_str(), welcome.size(), 0);

    std::string inputBuffer;
    char ch;

    while (true) {
        ssize_t n = recv(fd, &ch, 1, 0);  // Read 1 byte at a time

        if (n <= 0) {
            break; // client closed or error
        }

        if (ch == '\r') {
            // Ignore carriage return (common with Telnet)
            continue;
        }

        if (ch == '\n') {
            // Enter key pressed: echo the input
            std::string response = "Echo: " + inputBuffer + "\n";
            send(fd, response.c_str(), response.size(), 0);

            std::cout << "Client: " << inputBuffer << std::endl;
            inputBuffer.clear();  // Prepare for next line
        } else {
            inputBuffer += ch;
        }
    }

    std::cout << "Client disconnected.\n";
    close(fd);
    client_fd = -1;
}

void TelnetServer::closeSockets() {
    if (client_fd >= 0) close(client_fd);
    if (server_fd >= 0) close(server_fd);
}

ssize_t TelnetServer::writeData(const std::string &data) {
    return ssize_t();
}

std::string TelnetServer::readData(size_t maxLength) {
    return std::string();
}
