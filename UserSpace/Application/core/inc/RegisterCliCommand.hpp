/******************************************************************************
 *  @file       RegisterCliCommand.hpp
 *  @brief      Implements CLI command registeration linkerset
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

#ifndef _REGISTER_CLI_COMMAND_HPP_
#define _REGISTER_CLI_COMMAND_HPP_

#include "ErrorCodes.hpp"

#include <string>
#include <vector>

struct CliCommand {
    const char* name;
    Codes (*write)(const std::vector<std::string>& args);
    Codes (*read)(std::string& data);
    Codes (*help)(std::string& data);
};

#define CLI_SECTION __attribute__((section(".cli_cmds"), used))
#define USED_ATTR __attribute__((used))

#define REGISTER_CLI_COMMAND_WRITE(name, ClassName, WriteMethod, HelpMethod)                                                                    \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) USED_ATTR;                                    \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) USED_ATTR;                                                        \
                                                                                                                                                \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) {                                             \
        return ClassName::getInstance().WriteMethod(args);                                                                                      \
    }                                                                                                                                           \
                                                                                                                                                \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) {                                                                 \
        return ClassName::getInstance().HelpMethod(data);                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static const CliCommand __cmd_##ClassName##_##WriteMethod CLI_SECTION USED_ATTR = {                                                         \
        name, __##ClassName##_##WriteMethod##_trampoline, nullptr, __##ClassName##_##HelpMethod##_trampoline                                    \
    }                                                                                                                                           \

#define REGISTER_CLI_COMMAND_READ(name, ClassName, ReadMethod, HelpMethod)                                                                      \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) USED_ATTR;                                                        \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) USED_ATTR;                                                        \
                                                                                                                                                \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) {                                                                 \
        return ClassName::getInstance().ReadMethod(data);                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) {                                                                 \
        return ClassName::getInstance().HelpMethod(data);                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static const CliCommand __cmd_##ClassName##_##ReadMethod CLI_SECTION USED_ATTR = {                                                          \
        name, nullptr, __##ClassName##_##ReadMethod##_trampoline, __##ClassName##_##HelpMethod##_trampoline                                     \
    }                                                                                                                                           \

#define REGISTER_CLI_COMMAND_FULL(name, ClassName, WriteMethod, ReadMethod, HelpMethod)                                                         \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) USED_ATTR;                                    \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) USED_ATTR;                                                        \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) USED_ATTR;                                                        \
                                                                                                                                                \
    static Codes __##ClassName##_##WriteMethod##_trampoline(const std::vector<std::string>& args) {                                             \
        return ClassName::getInstance().WriteMethod(args);                                                                                      \
    }                                                                                                                                           \
                                                                                                                                                \
    static Codes __##ClassName##_##ReadMethod##_trampoline(std::string& data) {                                                                 \
        return ClassName::getInstance().ReadMethod(data);                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static Codes __##ClassName##_##HelpMethod##_trampoline(std::string& data) {                                                                 \
        return ClassName::getInstance().HelpMethod(data);                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static const CliCommand __cmd_##ClassName##_##ReadMethod CLI_SECTION USED_ATTR = {                                                          \
        name, __##ClassName##_##WriteMethod##_trampoline, __##ClassName##_##ReadMethod##_trampoline, __##ClassName##_##HelpMethod##_trampoline  \
    }                                                                                                                                           \


#endif // _REGISTER_CLI_COMMAND_HPP_
