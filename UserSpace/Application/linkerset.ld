/***********************************************************************************
 *  @file       linkerset.ld
 *  @brief      Linker script to define linkerset sections for application
 *              running on embedded Linux systems.
 *
 *  @copyright  Copyright (c) 2025 Kishwar Kumar
 *              All rights reserved.
 *
 *  @license    This project is publicly available on GitHub for viewing and
 *              educational/reference purposes only. Redistribution, modification,
 *              or commercial use of any portion of this script is strictly
 *              prohibited without prior written permission from the author.
 *
 *  @author     Kishwar Kumar
 *  @version    1.0
 *
 *  @note       This script defines sorted sections (.cli_cmds, .init_calls, ...)
 *              to be used with GCC's linkersets. It is intended for use in embedded
 *              systems such as Yocto-based Linux on Raspberry Pi.
 ***********************************************************************************/

SECTIONS {
    .cli_cmds : ALIGN(4) {
        __start_cli_cmds = .;
        KEEP(*(.cli_cmds))
        __stop_cli_cmds = .;
    }

    .init_calls : ALIGN(4) {
        __start_init_calls = .;
        KEEP(*(.init_calls))
        __stop_init_calls = .;
    }

    .queue_registry : ALIGN(4) {
        __start_queue_registry = .;
        KEEP(*(.queue_registry))
        __stop_queue_registry = .;
    }
}
INSERT AFTER .data;
