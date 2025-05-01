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

#include "TelnetServer.hpp"
#include "AutoInit.hpp"

#include <vector>
#include <string>

struct CLICommand {
    const char* name;
    int (*handler)(const std::vector<std::string>& args);
};

#define CLI_SECTION __attribute__((section("cli_cmds")))
#define CLI_COMMAND_REGISTER(name, ClassName, MethodName)                                           \
    static int __##ClassName##_##MethodName##_trampoline(const std::vector<std::string>& args) {    \
        return ClassName::getInstance().MethodName(args);                                           \
    }                                                                                               \
    static const CLICommand __cmd_##ClassName##_##MethodName CLI_SECTION __attribute__((used)) = {  \
        name, __##ClassName##_##MethodName##_trampoline                                             \
    }                                                                                               \


class CLI : public TelnetServer {
public:
    static CLI& getInstance() {
        static CLI instance;
        return instance;
    }

    CLI() : TelnetServer(PORT) {}
    ~CLI() = default;

    void write() override;
    void read() override;
private:
    static constexpr uint16_t PORT = 23;
    std::vector<std::string> tokenize(const std::string& input);
    int executeCommand(const std::string& input);
};

REGISTER_AUTO_INIT(CLI)

#endif  // _CLI_HPP_
