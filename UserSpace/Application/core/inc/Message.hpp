/******************************************************************************
 *  @file       Message.hpp
 *  @brief      Implements message structure for communication between services,
 *              including support for ownership-based payload, sender reference,
 *              and message priority.
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

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <memory>
#include <chrono>

enum class Priority {
    LOW, MEDIUM, HIGH
};

template <typename T>
struct Message {
    Queue<Message<T>>* senderQueue;                     // So receiver can send a reply
    Priority priority;                                  // Optional message priority
    std::unique_ptr<T> data;                            // Auto-cleared after processing
    std::chrono::steady_clock::time_point timestamp;    // time stamp

    Message(Message<Queue<T>>* sender, Priority prio, std::unique_ptr<T> payload) : senderQueue(sender),
                                                                                    priority(prio),
                                                                                    data(payload),
                                                                                    timestamp(std::chrono::steady_clock::now()) {
    }

    // Move-only: to preserve unique_ptr semantics
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
    Message(Message&&) noexcept = default;
    Message& operator=(Message&&) noexcept = default;
};

#endif // _MESSAGE_HPP_
