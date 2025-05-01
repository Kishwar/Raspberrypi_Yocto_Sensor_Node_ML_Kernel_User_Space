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

#include "Cli.hpp"

#include <thread>

#if 0
// header needed
#include "Thread.hpp"

void task(const std::string& name, int val) {
    for(int i=0; i<10; i++)
    {
        std::cout << "Task " << name << ": value = " << val << std::endl;
        sleep(2);
    }
}

// how to use
Thread t(task, 10, 1024 * 1024, Thread::Policy::FIFO, "MyThread", 42);
t.start();
t.join();
#endif

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


int main() {
    try {
        CLI& cli = CLI::getInstance();
        while (true) {
            // Your main app logic here (or just sleep)
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
    return 0;
}