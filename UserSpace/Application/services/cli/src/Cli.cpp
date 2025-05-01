#include "Cli.hpp"
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
#include "Logging.hpp"

#include <sstream>

extern const CLICommand __start_cli_cmds[];
extern const CLICommand __stop_cli_cmds[];

void CLI::write()
{

}

void CLI::read()
{
    while(true) {
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

int CLI::executeCommand(const std::string& input) {
    auto tokens = tokenize(input);
    if (tokens.empty()) return -1;

    const std::string& cmd = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    for (const CLICommand* c = __start_cli_cmds; c < __stop_cli_cmds; ++c) {
        if (cmd == c->name) {
            PRINTLOG(Level::INFO, "2. cmd " << cmd << " c->name " << c->name << " found, calling handle");
            return c->handler(args);
        }
    }

    return -1;
}
