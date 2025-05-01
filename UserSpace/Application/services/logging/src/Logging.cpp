/******************************************************************************
 *  @file       Logging.cpp
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

#include "Logging.hpp"

#include <iostream>

Logging::Logging() : TelnetServer(PORT),
                     level_(Level::INFO),
                     queue_(std::make_unique<Queue<std::string>>()) {
}

void Logging::log(const Level level, const std::string &content) {
    const char* color = "";
    const char* label = "";

    if(level > level_) return;

    switch (level)
    {
        case Level::INFO:
            color = "\033[0m";
            label = "[INFO]\t";
            break;
        case Level::DEBUG:
            color = "\033[1;34m";
            label = "[DEBUG]\t";
            break;
        case Level::ERROR:
            color = "\033[1;31m";
            label = "[ERROR]\t";
            break;
        case Level::FATAL:
            color = "\033[1;41m\033[1;37m";
            label = "[FATAL]\t";
            break;
        case Level::MEDIUM:
            color = "\033[1;33m";
            label = "[MEDIUM]";
            break;
        case Level::HIGH:
            color = "\033[1;35m";
            label = "[HIGH]\t";
            break;
        default:
            color = "\033[0m";
            label = "[UNKNOWN]\t";
            break;
    }

    std::ostringstream oss;
    oss << "\r" << color << label << " " << content << "\033[0m" << "\r" << std::endl;

    // log on local terminal
    std::cout << oss.str();

    // log on socket interface
    queue_->send(oss.str());
}

int Logging::setLevel(const std::vector<std::string>& args) {
    
    return 0;
}

void Logging::write() {
    while(true) {
        std::string val = queue_->receive();
        sockWrite(val);
    }
}

void Logging::read() {
    /* ---- THERE IS NO READ OPERATION FOR LOGGING ---- */
}
