/*
 * sensor.h - Custom I2C driver for Bosch BME280 sensor
 *
 * Author: Kishwar Kumar
 * Date:   2025-03-22
 *
 * Description:
 *   This is a custom Linux kernel driver for the BME280 environmental sensor.
 *   The driver is written for personal use, learning, and experimentation.
 *   It communicates with the BME280 over I2C to retrieve temperature,
 *   pressure, and humidity data.
 *
 * License: GNU General Public License v2.0
 *
 * Notes:
 *   - Written for use with the Yocto Project on embedded Linux.
 *   - Designed to be simple and minimalistic for educational purposes.
 */

#include <linux/types.h>


int open(struct inode *inode, struct file *file);
int release(struct inode *inode, struct file *file);
ssize_t read(struct file *file, char __user *buf, size_t len, loff_t *offset);
ssize_t write(struct file *file, const char __user *buf, size_t len, loff_t *offset);