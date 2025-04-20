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

#include <iostream>
#include <unistd.h>

#include "Thread.hpp"

#if 0
// header needed
#include "Timer.hpp"

void print_bool_message(const std::string& msg, int count, bool print) {
    std::cout << "[Timer] " << msg << " #" << count << " bool " << print << std::endl;
}

// how to use
bool bl = false;
Timer timer(print_bool_message, 1000, Timer::Type::Periodic, message, value, bl);
timer.start();
timer.stop();
std::cout << "Timer stopped.\n";
#endif

void task(const std::string& name, int val) {
    for(int i=0; i<10; i++)
    {
        std::cout << "Task " << name << ": value = " << val << std::endl;
        sleep(2);
    }
}

int main() {
    Thread t1(task, 10, 1024 * 1024, Thread::Policy::FIFO, "MyThread", 42);
    Thread t2(task, 60, 1024 * 1024, Thread::Policy::FIFO, "MyThread", 43);
    t1.start();
    t2.start();
    t2.join();
    t2.join();
    return 0;
}