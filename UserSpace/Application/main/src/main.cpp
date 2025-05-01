/******************************************************************************
 *  @file       main.cpp
 *  @brief      main file of the project
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

#include <iostream>
#include <unistd.h>

#include "Cli.hpp"
#include "Logging.hpp"
#include "LoggingIf.hpp"

#include <thread>

int main() {
    try {
        CLI& cli = CLI::getInstance();
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::FATAL, "new traces sent to telnet");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::ERROR, "new traces sent to telnet");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::INFO, "new traces sent to telnet");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::DEBUG, "new traces sent to telnet");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::MEDIUM, "new traces sent to telnet");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            PRINTLOG(Level::HIGH, "new traces sent to telnet");
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
    return 0;
}