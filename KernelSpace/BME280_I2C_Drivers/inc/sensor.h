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
#ifndef BMP280_SENSOR_H
#define BMP280_SENSOR_H

#include <linux/fs.h>

extern const struct file_operations bmp_fops;

/**
 * @brief 
 */
void init(i2c_client *client);

/**
 * @brief 
 * 
 * @param inode 
 * @param file 
 * @return int 
 */
int open(struct inode *inode, struct file *file);

/**
 * @brief 
 * 
 * @param inode 
 * @param file 
 * @return int 
 */
int release(struct inode *inode, struct file *file);

/**
 * @brief 
 * 
 * @param file 
 * @param buf 
 * @param len 
 * @param offset 
 * @return ssize_t 
 */
ssize_t read(struct file *file, char __user *buf, size_t len, loff_t *offset);

/**
 * @brief 
 * 
 * @param file 
 * @param buf 
 * @param len 
 * @param offset 
 * @return ssize_t 
 */
ssize_t write(struct file *file, const char __user *buf, size_t len, loff_t *offset);

#endif // BMP280_SENSOR_H
