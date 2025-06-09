/******************************************************************************
 *  @file       Help.hpp
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

#ifndef _HELP_HPP_
#define _HELP_HPP_

#include "RegisterCliCommand.hpp"

class Help {
public:
    static Help& getInstance() {
        static Help instance;
        return instance;
    }

    Codes printHelp(std::string& data);
    Codes help(std::string& data);

private:
    Help() = default;
    ~Help() = default;
};

/* register CLI command with linkerset */
REGISTER_CLI_COMMAND_READ("help", Help, printHelp, help);

#endif // _HELP_HPP_
