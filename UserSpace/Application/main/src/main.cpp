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
#include <csignal>
#include <time.h>
#include <unistd.h>
#include <thread>

void timer_callback(union sigval val) {
    std::cout << "Timer callback fired!" << std::endl;
}

void thread_task() {
    while (true) {
        std::cout << "Thread Task ..." << std::endl;
        sleep(10);
    }
}

int main() {
    timer_t timer_id;
    std::thread t1(thread_task);  // Start thread for task1

    struct sigevent sev {};
    struct itimerspec its {};

    sev.sigev_notify = SIGEV_THREAD;              // Call callback in new thread
    sev.sigev_notify_function = timer_callback;   // Your callback
    sev.sigev_value.sival_ptr = nullptr;          // Optional data to pass

    if (timer_create(CLOCK_REALTIME, &sev, &timer_id) == -1) {
        perror("timer_create");
        return 1;
    }

    its.it_value.tv_sec = 1;       // First trigger
    its.it_interval.tv_sec = 10;    // Repeat every 10 seconds

    if (timer_settime(timer_id, 0, &its, nullptr) == -1) {
        perror("timer_settime");
        return 1;
    }

    std::cout << "Main thread continues..." << std::endl;

    // Keep the main thread alive to let timer callbacks happen
    while (true) {
        std::cout << "Main Thread..." << std::endl;
        sleep(10);
    }

    t1.join();  // Wait for t1 to finish

    return 0;
}