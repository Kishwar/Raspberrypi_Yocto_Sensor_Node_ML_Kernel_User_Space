/******************************************************************************
 *  @file       QueueHandle.hpp
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

#ifndef _QUEUE_HANDLE_HPP_
#define _QUEUE_HANDLE_HPP_

#include <string>

struct QueueHandle {
    const std::string name;
    void* queue;
};

extern QueueHandle __start_queue_registry[];
extern QueueHandle __stop_queue_registry[];

#define QUEUE_SECTION __attribute__((section(".queue_registry"), used))

// Put this in the class definition (e.g., in `Cli.hpp`)
#define DECLARE_QUEUE_FRIEND(CLASSNAME, MEMBER) \
    friend struct CLASSNAME##_##MEMBER##_Registrar;

// Put this in the .cpp file after defining the static member
#define REGISTER_PRIVATE_QUEUE(CLASSNAME, MEMBER, NAMESTR)                  \
    struct CLASSNAME##_##MEMBER##_Registrar {                               \
        static QueueHandle handle;                                          \
    };                                                                      \
    QueueHandle CLASSNAME##_##MEMBER##_Registrar::handle                    \
        QUEUE_SECTION = { NAMESTR, static_cast<void*>(&CLASSNAME::MEMBER) };

inline QueueHandle* findQueueByName(const std::string& name) {
    for (QueueHandle* it = __start_queue_registry; it < __stop_queue_registry; ++it) {
        if (it->name == name)
            return it;
    }
    return nullptr;
}

#endif  // _QUEUE_HANDLE_HPP_
