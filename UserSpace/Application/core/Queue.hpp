/******************************************************************************
 *  @file       Queue.hpp
 *  @brief      Implements Queue to send / receive messages from different
 *              services
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

#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue {
public:
    void send(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        cond_.notify_one();
    }

    T receive() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [&] {
                                return !queue_.empty();
                             });
        T item = queue_.front();
        queue_.pop();
        return T;
    }

    bool receive_with_timeout(T& item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if(cond_.wait_for(lock, timeout, [&] {
                                                return !queue_.empty();
                                             })) {
            item = queue_.front();
            queue_.pop();
            return true;
        }
        return false;
    }

    bool is_empty() {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif  // _QUEUE_HPP_
