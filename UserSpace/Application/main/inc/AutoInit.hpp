/******************************************************************************
 *  @file       AutoInit.cpp
 *  @brief      Implements auto initializer registeration linkerset
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

#ifndef _AUTOINIT_HPP_
#define _AUTOINIT_HPP_

using InitFunc = void (*)();

#define INIT_SECTION __attribute__((section("init_calls")))
#define REGISTER_AUTO_INIT(ClassName)                                                                       \
    static void __##ClassName##_initCaller() {                                                              \
        ClassName::getInstance();                                                                           \
    }                                                                                                       \
    static InitFunc __init_##ClassName INIT_SECTION __attribute__((used)) = __##ClassName##_initCaller;     \

#endif // _AUTOINIT_HPP_
