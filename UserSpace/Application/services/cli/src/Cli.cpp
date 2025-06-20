/******************************************************************************
 *  @file       Cli.cpp
 *  @brief      Implements CLI service runs over telnet
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

#include "Cli.hpp"
#include "RegisterCliCommand.hpp"

#include <sstream>

extern const CliCommand __start_cli_cmds[];
extern const CliCommand __stop_cli_cmds[];

Queue<std::string> CLI::cliQ;

CLI::CLI() : TelnetServer(PORT) {
}

void CLI::write() {
    while(true) {
        sockWrite(cliQ.receive());
    }
}

void CLI::read() {
    while(true) {
        cliQ.send("CLI>");
        std::string val = sockRead('\n');
        executeCommand(val);
    }
}

std::vector<std::string> CLI::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(input);

    while (std::getline(ss, token, ',')) {
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            tokens.emplace_back(token.substr(start, end - start + 1));
        else
            tokens.emplace_back("");  // handle empty
    }

    return tokens;
}

Codes CLI::executeCommand(const std::string& input) {
    auto tokens = tokenize(input);
    Codes ret = Codes::CODE_GENERIC_ERROR; 

    if (tokens.empty()) {
        ret = Codes::CODE_INVALID_PARAM;
        return ret;
    }

    const std::string& cmd = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    for (const CliCommand* c = __start_cli_cmds; c < __stop_cli_cmds; ++c) {
        if (cmd == c->name) {
            if((tokens.size() == 1) && (c->read != nullptr)) {
                // read operation
                std::string outData;
                ret = c->read(outData);
                if(Codes::CODE_NO_ERROR == ret) {
                    cliQ.send("\r\n");
                    cliQ.send(outData);
                    cliQ.send("\r\n");
                    break;
                }
            } else {
                // write operation
                ret = c->write(args);
                break;
            }
        }
    }
    cliQ.send(errCodeStr(ret));
    cliQ.send("\r\n");
    return ret;
}

std::string CLI::errCodeStr(Codes code) {
    switch(code) {
        case Codes::CODE_NO_ERROR:
            return "\r\nOK\r\n";
        default:
            return "\r\nERROR\r\n";
    }
}
