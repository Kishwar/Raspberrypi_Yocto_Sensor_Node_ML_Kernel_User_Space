/******************************************************************************
 *  @file       Thread.hpp
 *  @brief      Implements Thread using POSIX APIs
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

#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include <csignal>
#include <functional>
#include <tuple>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <pthread.h>

class Thread {
public:
    enum class Policy {
        OTHER = SCHED_OTHER,
        FIFO = SCHED_FIFO,
        RR   = SCHED_RR
    };

    enum class State {
        JOIN = PTHREAD_CREATE_JOINABLE,
        DETACH = PTHREAD_CREATE_DETACHED
    };

    template <typename T, typename... Args>
    Thread(T&& callback, int prio, size_t stackSize, Policy policy, State state, Args&&... args)
         : priority_(prio),
           stack_size_(stackSize),
           policy_(static_cast<int>(policy)),
           state_(static_cast<int>(state))
    {
        func_ = [cb = std::forward<T>(callback),
                 tup = std::make_tuple(std::forward<Args>(args)...)]() mutable {
                    std::apply(cb, tup);
        };
    }

    void start() {
        pthread_attr_init(&attr_);

        // Set stack size if requested
        if (stack_size_ > 0) {
            pthread_attr_setstacksize(&attr_, stack_size_);
        }

        // Set scheduling policy
        pthread_attr_setschedpolicy(&attr_, policy_);
        pthread_attr_setinheritsched(&attr_, PTHREAD_EXPLICIT_SCHED);

        // Set thread priority
        sched_param param{};
        param.sched_priority = priority_;
        pthread_attr_setschedparam(&attr_, &param);

        // set thread State
        pthread_attr_setdetachstate(&attr_, state_);

        // Create thread
        if (pthread_create(&thread_, &attr_, [](void* arg) -> void* {
                                                auto* self = static_cast<Thread*>(arg);
                                                if (self->func_)
                                                {
                                                    self->func_();
                                                }
                                                return nullptr;
                                             }, this) != 0) {
            throw std::runtime_error("Failed to create thread");
        }
    }

    void join() {
        pthread_join(thread_, nullptr);
    }

    ~Thread() {
        pthread_attr_destroy(&attr_);
    }

private:
    pthread_t thread_;
    pthread_attr_t attr_;
    std::function<void()> func_;
    int priority_;
    size_t stack_size_;
    int policy_;
    int state_;
};

#endif // _THREAD_HPP_
