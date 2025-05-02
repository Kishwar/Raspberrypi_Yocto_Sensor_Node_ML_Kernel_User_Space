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

#include "CliErrorCodesIf.hpp"
#include "TelnetServer.hpp"
#include "AutoInit.hpp"
#include "Queue.hpp"

#include <vector>
#include <string>

struct CLICommand {
    const char* name;
    Codes (*write)(const std::vector<std::string>& args);
    Codes (*read)(std::string& data);
};

#define CLI_SECTION __attribute__((section("cli_cmds")))
#define CLI_COMMAND_WRITE(name, ClassName, WriteMethod)                                                 \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) {     \
        return ClassName::getInstance().WriteMethod(args);                                              \
    }                                                                                                   \
    static const CLICommand __cmd_##ClassName##_##WriteMethod CLI_SECTION __attribute__((used)) = {     \
        name, __##ClassName##_##WriteMethod##_trampoline, nullptr                                       \
    }                                                                                                   \

#define CLI_COMMAND_READ(name, ClassName, ReadMethod)                                                   \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) {                         \
        return ClassName::getInstance().ReadMethod(data);                                               \
    }                                                                                                   \
    static const CLICommand __cmd_##ClassName##_##ReadMethod CLI_SECTION __attribute__((used)) = {      \
        name, nullptr, __##ClassName##_##ReadMethod##_trampoline                                        \
    }                                                                                                   \

#define CLI_COMMAND_REGISTER_BOTH(name, ClassName, WriteMethod, ReadMethod)                             \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) {     \
        return ClassName::getInstance().WriteMethod(args);                                              \
    }                                                                                                   \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) {                         \
        return ClassName::getInstance().ReadMethod(data);                                               \
    }                                                                                                   \
    static const CLICommand __cmd_##ClassName##_##ReadMethod CLI_SECTION __attribute__((used)) = {      \
        name, __##ClassName##_##WriteMethod##_trampoline, __##ClassName##_##ReadMethod##_trampoline     \
    }                                                                                                   \

class CLI : public TelnetServer {
public:
    static CLI& getInstance() {
        static CLI instance;
        return instance;
    }

    CLI();
    ~CLI() = default;

    void write() override;
    void read() override;
private:
    static constexpr uint16_t PORT = 23;
    std::unique_ptr<Queue<std::string>> queue_;

    std::vector<std::string> tokenize(const std::string& input);
    Codes executeCommand(const std::string& input);
    std::string errCodeStr(Codes code);
};

/* register class to be auto-activated at startup (linkerset) */
REGISTER_AUTO_INIT(CLI)

#endif  // _CLI_HPP_
