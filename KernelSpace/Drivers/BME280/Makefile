# Define where your kernel is built
KDIR ?= /home/kkumar/embd_linux/build_pi/tmp/work/raspberrypi3-poky-linux-gnueabi/linux-raspberrypi/1_5.15.92+gitAUTOINC+509f4b9d68-r0/linux-raspberrypi3-standard-build

# Architecture and compiler (usually set by environment-setup script)
ARCH ?= arm
CROSS_COMPILE ?= arm-poky-linux-gnueabi-

# Where your module source and headers are
SRC_DIR := src
INC_DIR := inc

# Module name
obj-m := mymodule.o

# Add include path for your headers
EXTRA_CFLAGS += -I$(PWD)/$(INC_DIR)

# List all .c files in src/
mymodule-objs := $(patsubst $(SRC_DIR)/%.c, %.o, $(wildcard $(SRC_DIR)/*.c))

.PHONY: all clean

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
