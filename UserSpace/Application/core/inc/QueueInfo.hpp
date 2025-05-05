/******************************************************************************
 *  @file       QueueInfo.hpp
 *  @brief      Implements Queue registeration linkerset
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

#ifndef _QUEUE_INFO_HPP_
#define _QUEUE_INFO_HPP_

#include <string.h>

struct QueueInfo {
    const char* name;
    void* queue;  // raw pointer; upcast from Queue<T>*
};

#define QUEUE_SECTION __attribute__((section(".queue_registry"), used))
#define USED_ATTR __attribute__((used))

#define REGISTER_QUEUE(qname, qptr)                                             \
    static QueueInfo qinfo_##qname QUEUE_SECTION = { #qname, (void*)qptr };     \

extern QueueInfo __start_queue_registry[];
extern QueueInfo __stop_queue_registry[];

QueueInfo* findQueueByName(const char* name) {
    for (QueueInfo* it = __start_queue_registry; it < __stop_queue_registry; ++it) {
        if (strcmp(it->name, name) == 0)
            return it;
    }
    return nullptr;
}

#endif  // _QUEUE_INFO_HPP_
