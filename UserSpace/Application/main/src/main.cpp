/******************************************************************************
 *  @file       main.cpp
 *  @brief      main file of the project
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

#include "RegisterAutoInit.hpp"
#include "RegisterQueueHandle.hpp"

#include <thread>
#include <iostream>

extern InitFunc __start_init_calls[];
extern InitFunc __stop_init_calls[];

void callAllInitializers() {
    for (InitFunc* fn = __start_init_calls; fn < __stop_init_calls; ++fn) {
        (*fn)();  // calls Class::getInstance() indirectly
    }
}

int main() {
    try {
        callAllInitializers();  // ⚡ automatically initializes CLI, Logging, etc.
        while (true) {
            QueueHandle* q1 = findQueueByName("CLIQ");
            QueueHandle* q2 = findQueueByName("CLQ");

            std::cout << "Queue pointer -> Q1: " << q1 << "\nQueue pointer -> Q2: " << q2 << std::endl; 
            std::this_thread::sleep_for(std::chrono::seconds(300));
        }
    } catch (const std::exception& e) {
    }

    return 0;
}
