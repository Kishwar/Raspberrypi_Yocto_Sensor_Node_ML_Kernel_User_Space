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
```bash
PACKAGECONFIG:append:pn-gcc-runtime = " static-libstdc++"
DISTRO_FEATURES:append = " staticdev"
SDKIMAGE_FEATURES:append = " staticdev-pkgs"
```

Run following commands
```bash
kkumar@DESKTOP-NK9HSKR:~/embd_linux$ source poky/oe-init-build-env build_pi
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake -c cleansstate gcc-runtime
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake gcc-runtime
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake core-image-minimal -c populate_sdk
```
```bash
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ cd tmp/deploy/sdk/
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi/tmp/deploy/sdk$ ./poky-glibc-x86_64-core-image-minimal-cortexa7t2hf-neon-vfpv4-raspberrypi3-toolchain-4.0.21.sh
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi/tmp/deploy/sdk$ . /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
```

# Build Application
```bash
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application$ source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application$ make
```

# Build Kernel Module
```bash
kkumar@DESKTOP-NK9HSKR:~/embd_linux$ source poky/oe-init-build-env build_pi
kkumar@DESKTOP-NK9HSKR:~/embd_linux/build_pi$ bitbake virtual/kernel -c devshell
```

# Plug Application to systemd for auto-reload

## Step.1: Binaries path
```bash
root@raspberrypi3:/home# ls -la application 
-rwxr-xr-x    1 root     root        298292 Apr 21 10:56 application
```
## Step.2: Create a service file
```bash
sudo nano /etc/systemd/system/myapp.service
```

## Step.3: Paste this in file above
```bash
[Unit]
Description=EmbeddedApp
After=network.target

[Service]
ExecStart=/home/application
Restart=on-failure
User=pi
WorkingDirectory=/home

[Install]
WantedBy=multi-user.target
```

## Step.4: Reload systemd and enable it
```bash
sudo systemctl daemon-reexec
sudo systemctl daemon-reload
sudo systemctl enable myapp.service
sudo systemctl start myapp.service
```

## Step.5: Now it will auto-run on every boot! (To check its status or logs)
```bash
sudo systemctl status myapp.service
journalctl -u myapp.service
```

# Plug Kernel Module (.ko) to systemd for auto-reload

## Step.1: Create service file
```bash
sudo nano /etc/systemd/system/mydrivers.service
```

## Step.2: Paste this in file above
```bash
# /etc/systemd/system/mydrivers.service
[Unit]
Description=Load custom kernel module
Before=multi-user.target

[Service]
Type=oneshot
ExecStart=/sbin/modprobe mydrivers
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target
```

## Step.3: Reload systemd and enable it
```bash
sudo systemctl daemon-reload
sudo systemctl enable mydrivers
sudo systemctl start mydrivers
```

## Step.4: Now it will auto-reload on every boot! (To check its status or logs)
```bash
lsmod | grep mydrivers
# OR
dmesg | grep mydrivers
```



