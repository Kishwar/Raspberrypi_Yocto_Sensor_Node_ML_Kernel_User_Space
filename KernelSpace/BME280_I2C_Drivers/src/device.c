/*
 * device.c - Custom I2C driver for Bosch BME280 sensor
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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/i2c.h>

#include "sensor.h"

/* meta information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kishwar Kumar");
MODULE_DESCRIPTION("This is a basic Linux kernel drivers for i2c connecting BMP280.");

/**
 * static function declaration
 */
static int __init ModuleBmp280SensorNodeInit(void);
static void __exit ModuleCharacterDeviceExit(void);

/* Defines for device identification */ 
#define I2C_BUS_AVAILABLE	          1	         	        /* The I2C Bus available on the raspberry */
#define SLAVE_DEVICE_NAME	          "bmp280"	          /* Device and Driver Name */
#define BMP280_SLAVE_ADDRESS	      0x76		            /* BMP280 I2C address */

static const struct i2c_device_id id[] =
{
  {
    .name = SLAVE_DEVICE_NAME,
    .driver_data = 0
  }, 
  {
    .name = "",
    .driver_data = 0
  }
};

static struct i2c_driver driver =
{
	.driver =
  {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};

static struct i2c_board_info board_info =
{
	.type = SLAVE_DEVICE_NAME,
  .addr = BMP280_SLAVE_ADDRESS
};

static const struct file_operations bmp_fops = {
    .owner   = THIS_MODULE,
    .open    = open,
    .release = release,
    .read    = read,
    .write   = write,
};

// device number for this module
dev_t device_number;

// cdev variable
struct cdev bmp_cdev;

// class pointer
static struct class *bmp_class;

// i2c pointers
struct i2c_adapter *adap;
struct i2c_client *client;

module_init(ModuleBmp280SensorNodeInit);
module_exit(ModuleBmp280SensorNodeExit);

// --------------- Init & Exit ---------------
/**
 * @brief This function is called, when the module is loaded into the kernel
 * @return 0 when module init OK, non-zero otherwise
 */
static int __init ModuleBmp280SensorNodeInit(void)
{
  int ret = 0;
  printk(KERN_INFO "%s()\n", __func__);

  // 1. dynamically allocate a device number (creates device number)
  if((ret = alloc_chrdev_region(&device_number, 0 /*first minor*/, 1 /*counts*/, SLAVE_DEVICE_NAME)) < 0)
  {
    printk(KERN_INFO "%s() Failed to allocate a major number\n", __func__);
    return ret;
  }

  // 2. Initialize and add cdev
  cdev_init(&bmp_cdev, &bmp_fops);
  bmp_cdev.owner = THIS_MODULE;

  // 2a. register a device (cdev structure) with VFS
  if((ret = cdev_add(&bmp_cdev, dev_number, 1)) < 0)
  {
    printk(KERN_ERR "%s() Failed to add cdev\n", __func__);
    goto err_cdev;
  }

  /* ---- Create device class & device node for udev to create /dev file ---- */

  // 3. Create device class
  bmp_class = class_create(THIS_MODULE, SLAVE_DEVICE_NAME);
  if (IS_ERR(bmp_class)) 
  {
    printk(KERN_ERR "%s() Failed to create device class\n", __func__);
    ret = PTR_ERR(bmp_class);
    goto err_class;
  }

  // 4. Create device node /dev/bmp280
  if (device_create(bmp_class, NULL, dev_number, NULL, SLAVE_DEVICE_NAME) == NULL)
  {
    printk(KERN_ERR "%s() Failed to create device node\n", __func__);
    ret = -ENOMEM;
    goto err_device;
  }

  printk(KERN_INFO "%s() bmp280 registered successfully at /dev/%s\n", __func__, DEVICE_NAME);

  /* ---- Let's talk to I2C drivers and see what we get (non-device tree implementation) ---- */
  
  if((adap = i2c_get_adapter(I2C_BUS_AVAILABLE)) == NULL)
  {
    printk(KERN_ERR "%s() unable to get i2c adaptor...\n", __func__);
    ret = -1;
    goto err_device;
  }

  if((client = i2c_new_client_device(adap, &board_info)) == NULL)
  {
    printk(KERN_ERR "%s() unable to get i2c device...\n", __func__);
    ret = -1;
    goto err_device;
  }






err_device:
  class_destroy(bmp_class);
err_class:
    cdev_del(&bmp_cdev);
err_cdev:
    unregister_chrdev_region(dev_number, 1);
    return ret;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleCharacterDeviceExit(void)
{

}
