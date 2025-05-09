/******************************************************************************
 *  @file       Cli.hpp
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

#ifndef _CLI_HPP_
#define _CLI_HPP_

#include "ErrorCodes.hpp"
#include "TelnetServer.hpp"
#include "AutoInit.hpp"
#include "CliCommand.hpp"
#include "Queue.hpp"

#include <vector>
#include <string>

class CLI : public TelnetServer {
public:
    static CLI& getInstance() {
        static CLI instance;
        return instance;
    }

    void write() override;
    void read() override;
private:
    static constexpr uint16_t PORT = 23;
    std::unique_ptr<Queue<std::string>> queue_;

    CLI();
    ~CLI() = default;

    std::vector<std::string> tokenize(const std::string& input);
    Codes executeCommand(const std::string& input);
    std::string errCodeStr(Codes code);
};

/* register class to be auto-activated at startup (linkerset) */
REGISTER_AUTO_INIT(CLI)

#endif  // _CLI_HPP_
