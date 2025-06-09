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
#include "Message.hpp"

#include <iostream>
#include <algorithm>

Logging::Logging() : TelnetServer(PORT),
                     level_(Level::INFO),
                     queue_(std::make_shared<Queue<Message<std::string>>>()) {
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

    // log on socket interface
    auto message = Message<std::string>(queue_, Priority::HIGH, std::make_unique<std::string>(oss.str()));
    queue_->send(std::move(message));
}

Codes Logging::setLevel(const std::vector<std::string>& args) {
    if(args.empty()) return Codes::CODE_INVALID_PARAM;
    std::string str = args[0];

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    if (str == "FATAL") {
        level_ = Level::FATAL;
        return Codes::CODE_NO_ERROR;
    } else if (str == "ERROR") {
        level_ = Level::ERROR;
        return Codes::CODE_NO_ERROR;
    } else if (str == "INFO") {
        level_ = Level::INFO;
        return Codes::CODE_NO_ERROR;
    } else if (str == "DEBUG") {
        level_ = Level::DEBUG;
        return Codes::CODE_NO_ERROR;
    } else if (str == "MEDIUM") {
        level_ = Level::MEDIUM;
        return Codes::CODE_NO_ERROR;
    } else if (str == "HIGH") {
        level_ = Level::HIGH;
        return Codes::CODE_NO_ERROR;
    }

    PRINTLOG(Level::ERROR, "Invalid argument: " << str);
    return Codes::CODE_INVALID_PARAM;
}

Codes Logging::getLevel(std::string& data) {
    switch(level_) {
        case Level::FATAL:
            data = "FATAL";
            break;
        case Level::ERROR:
            data = "ERROR";
            break;
        case Level::INFO:
            data = "INFO";
            break;
        case Level::DEBUG:
            data = "DEBUG";
            break;
        case Level::MEDIUM:
            data = "MEDIUM";
            break;
        case Level::HIGH:
            data = "HIGH";
            break;
    }
    return Codes::CODE_NO_ERROR;
}

Codes Logging::help(std::string &data)
{
    data = "\"loglevel\" (\"FATAL\", \"ERROR\", \"HIGH\", \"MEDIUM\", \"INFO\", \"DEBUG\")";
    return Codes::CODE_NO_ERROR;
}

void Logging::write() {
    while(true) {
        auto message = queue_->receive();
        sockWrite(message.extractPayload());
    }
}

void Logging::read() {
    /* ---- THERE IS NO READ OPERATION FOR LOGGING ---- */
}
