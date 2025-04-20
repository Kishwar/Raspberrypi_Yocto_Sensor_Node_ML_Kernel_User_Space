# Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space
In this project, I will develop following things.
-  Kernel device drivers for OLED connected with I2C
-  Kernel device drivers for OLED connected with SPI
-  Kernel device drivers for BME280 connected with SPI
-  User Application (Layered designed with C++17)
    - Read sensor data
    - Write it on Displays together with realtime clock
    - Send data to AWS server
    - Run AI Linear regression model on temprature / pressure / humidity (Edge processing)
 
# Hardware
![devshell](RapberryPi_Sensors_OLED_Ethernet.jpeg)

# Create SDK to build application for Raspberrypi running yocto
Add following lines to kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi/conf$ nano local.conf
```
PACKAGECONFIG:append:pn-gcc-runtime = " static-libstdc++"
DISTRO_FEATURES:append = " staticdev"
SDKIMAGE_FEATURES:append = " staticdev-pkgs"
```

Run following commands
```
kkumar@DESKTOP-NK9HSKR:~/embd_linux$ source poky/oe-init-build-env build_pi
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake -c cleansstate gcc-runtime
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake gcc-runtime
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake core-image-minimal -c populate_sdk
```
```
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ cd tmp/deploy/sdk/
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi/tmp/deploy/sdk$ ./poky-glibc-x86_64-core-image-minimal-cortexa7t2hf-neon-vfpv4-raspberrypi3-toolchain-4.0.21.sh
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi/tmp/deploy/sdk$ . /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
```

# Build Application
```
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application$ source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application$ make
```