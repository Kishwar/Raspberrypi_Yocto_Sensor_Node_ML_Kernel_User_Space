/******************************************************************************
 *  @file       Help.cpp
 *  @brief      Prints help for all registered CLI commands
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

#include "Help.hpp"

#include <unordered_set>

extern CliCommand __start_cli_cmds[];
extern CliCommand __stop_cli_cmds[];

Codes Help::printHelp(std::string& data) {
    std::unordered_set<std::string> seen;
    for(CliCommand* cmd = __start_cli_cmds; cmd < __stop_cli_cmds; ++cmd) {
        if (seen.insert(cmd->name).second) {
            std::string val;
            cmd->help(val);
            data += "> " + val + "\r\n";
        }
    }
    return Codes::CODE_NO_ERROR;
}

Codes Help::help(std::string& data) {
    data = "\"help\"";
    return Codes::CODE_NO_ERROR;
}