/******************************************************************************
 *  @file       NoCopy.hpp
 *  @brief      Base class to be extended by all the drived classes
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

#ifndef _NOCOPY_HPP
#define _NOCOPY_HPP

class NoCopy {
public:
    NoCopy() = default;
    virtual ~NoCopy() = default;

    NoCopy(const NoCopy&) = delete;            // Copy constructor deleted
    NoCopy& operator=(const NoCopy&) = delete; // Copy assignment deleted
    NoCopy(NoCopy&&) = delete;                 // Move constructor deleted
    NoCopy& operator=(NoCopy&&) = delete;      // Move assignment deleted
 };

 #endif // _NOCOPY_HPP
