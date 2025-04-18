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

 #ifndef _TIMER_HPP_
 #define _TIMER_HPP_

template <typename F, typename... Args>
class Timer {
public:
    enum class Type {
        OneShot,
        Periodic
    };

    Timer(T&& fn, int milliseconds, Type type, Args&& args)
        : callback_(std::forward<T>(fn)),
          args_(std::tuple(std::forward<Args>(args)...)),
          interval_ms_(milliseconds),
          type_(type),
          active_(false)
    {
        memset(&sev_, 0, sizeof(sev_));
        sev_.sigev_notify = SIGEV_THREAD;
        sev_.sigev_notify_function = [] (union sigval sv ){
                                        auto* self = static_cast<Timer*>(sv.sival_ptr);
                                        if (self) {
                                            self->invoke();
                                        }
                                     };
        sev_.sigev_value.sival_ptr = this;

        if(timer_create(CLOCK_REALTIME, &sev_, &timer_id_) != 0) {
            throw std::runtime_error("Failed to create timer: " + std::string(std::strerror(errno)));
        }
    }

    ~Timer() {
        stop();
        timer_delete(timer_id_);
    }

    void start() {
        if (active_) return;

        its_.it_value.tv_sec = interval_ms_ / 1000;
        its_.it_value.tv_nsec = (interval_ms_ % 1000) * 1'000'000;

        if (type_ == Type::Periodic) {
            its_.it_interval = its_.it_value;
        } else {
            its_.it_interval.tv_sec = 0;
            its_.it_interval.tv_nsec = 0;
        }

        if (timer_settime(timer_id_, 0, &its_, nullptr) != 0) {
            throw std::runtime_error("Failed to start timer: " + std::string(std::strerror(errno)));
        }

        active_ = true;
    }

    void stop() {
        if (!active_) return;

        struct itimerspec stop_spec = {};
        timer_settime(timer_id_, 0, &stop_spec, nullptr);
        active_ = false;
    }

private:
    T callback_;
    std::tuple<Args...> args_;
    timer_t timer_id_;
    struct sigevent sev_;
    struct itimerspec its_;
    int interval_ms_;
    Type type_;
    bool active_;
};

 #endif  // _TIMER_HPP_
 