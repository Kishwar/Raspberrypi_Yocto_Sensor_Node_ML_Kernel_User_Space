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
 
 void timer_callback(union sigval val) {
     std::cout << "Timer callback fired!\n";
     // You can access data via val.sival_ptr if needed
 }
 
 int main() {
     timer_t timer_id;
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
     its.it_interval.tv_sec = 1;    // Repeat every second
 
     if (timer_settime(timer_id, 0, &its, nullptr) == -1) {
         perror("timer_settime");
         return 1;
     }
 
     std::cout << "Main thread continues...\n";
 
     // Keep the main thread alive to let timer callbacks happen
     while (true) {
         sleep(10);
     }
 
     return 0;
 }