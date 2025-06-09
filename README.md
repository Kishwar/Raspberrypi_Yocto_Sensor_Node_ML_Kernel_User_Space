# Raspberry Pi Sensor Node with ML – Kernel & User Space Integration

This repository provides a modular embedded system targeting Raspberry Pi, combining:

- 🧠 **Machine Learning inference in user space**
- 📡 **Custom kernel modules for sensor drivers**
- 🧩 **Modular services with linker set-based registration**
- 🛠️ **Yocto-based SDK for cross-compilation**

---

## 🧠 Application Architecture

![Application Overview](Application_Overview_UserSpace.jpg)

This image outlines the architecture of the user-space application:
- Data flows from kernel drivers into queues
- Services (CLI, Telnet, Logging, etc.) communicate via queues
- ML model is integrated as a self-contained module
- All components register dynamically via **linker sets**

---

## 🛰️ Queue Overview
This project uses a unified messaging abstraction where services send messages to `Queue<T>` discovered via Linkersets. If a local handler `Queue<T>` is not found, the system automatically falls back to using **Protobuf serialization and gRPC** to communicate with a remote server.

![Queue Overview](Queue_Overview_UserSpace.jpg)

---

## 🌐 Protobuf Integration

This project uses [Protocol Buffers](https://developers.google.com/protocol-buffers) for message serialization between local and remote services. If a local queue is not found for a message, the system serializes it via Protobuf and sends it to a remote responder using UDP.

📂 Protobuf: [`protobuf/`](UserSpace/Application/protobuf)

---

## 🔗 gRPC Integration

This project integrates [gRPC](https://grpc.io/) as a fallback communication mechanism for service messages when no local queue is found. Messages are serialized using **Protocol Buffers**, and forwarded to a remote server over **gRPC** for further handling or execution.

Local services use `Queue<T>` with automatic discovery via **Linkersets**

When a queue is not available locally, the message is serialized using **Protobuf**

The serialized message is sent over **gRPC** to a remote server, which deserializes and handles it

📂 Protobuf definitions used for gRPC communication: [`protobuf/`](UserSpace/Application/protobuf)

This design allows seamless scaling from single-device embedded systems to distributed architectures involving multiple remote processing nodes.

---

## 📂 Project Structure

```
.
├── KernelSpace/Drivers            # Linux kernel modules for various physical sensors
├── UserSpace/Application          # User space application with various services
└── README.md
```

---

## ⚙️ What are Linker Sets?

**Linker sets** allow components to register themselves at link time, enabling automatic discovery and activation at runtime. This approach eliminates the need for manual initialization lists and supports a highly modular system.

```cpp
/* AutoInit registation */
REGISTER_AUTO_INIT(CLI)                                             // Register class for startup

/* Cli Command registation */
REGISTER_CLI_COMMAND_BOTH("loglevel", Logging, setLevel, getLevel)  // Register CLI command

/* Queue registation */
DECLARE_QUEUE_FRIEND(Example, ExampleQ)                             // Declare friend
REGISTER_PRIVATE_QUEUE(Example, ExampleQ, "ExampleQ")               // Register Q to be used by Example
```

This modular design avoids centralized registration, improves scalability, and simplifies extension.

---

## 🧰 Create Yocto SDK

On your Yocto build machine:

```bash
# nano embd_linux/build_pi/conf/local.conf
PACKAGECONFIG:append:pn-gcc-runtime = " static-libstdc++"
DISTRO_FEATURES:append = " staticdev"
SDKIMAGE_FEATURES:append = " staticdev-pkgs"
```
```bash
# cd ~/embd_linux
source poky/oe-init-build-env build_pi
bitbake -c cleansstate gcc-runtime
bitbake gcc-runtime
bitbake core-image-minimal -c populate_sdk
```

This will generate a `.sh` installer:

```bash
# poky-glibc-x86_64-core-image-minimal-cortexa7t2hf-neon-vfpv4-raspberrypi3-toolchain-4.0.21.sh
tmp/deploy/sdk/poky-glibc-x86_64-<sdkname>-armv7at2hf-neon-toolchain-*.sh
```

Then on your dev system:

```bash
# cd tmp/deploy/sdk
chmod +x poky-*.sh
./poky-*.sh
```

Source the environment to use it:

```bash
source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
```

---

## 🧪 Build User Space Application

```bash
cd UserSpace/Application
mkdir build && cd build
cmake ..
make -j$(nproc)
```

The output binary will be:

```
build/binaries/EmbeddedApp
```

---

## 🧱 Build Kernel Modules

```bash
cd KernelSpace/
source poky/oe-init-build-env build_pi
bitbake virtual/kernel -c devshell
```

---

## 🔄 Deploy with systemd

### Step 1: Move the Binary

```bash
scp build/binaries/EmbeddedApp <root>@<192.168.178.98>:/home/
ssh <root>@<192.168.178.98>
chmod +x /home/EmbeddedApp
```

### Step 2: Create a systemd Service

```bash
sudo nano /etc/systemd/system/EmbeddedApp.service
```

Paste:

```ini
[Unit]
Description=EmbeddedApp
After=network.target

[Service]
ExecStart=/home/EmbeddedApp
Restart=on-failure
User=root
WorkingDirectory=/home
RestartSec=3
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
```

### Step 3: Reload and Enable

```bash
[sudo] systemctl enable EmbeddedApp.service
[sudo] systemctl start EmbeddedApp.service
```

### Step 4: Monitor

```bash
systemctl status EmbeddedApp.service
journalctl -u EmbeddedApp.service
```

---

## 📄 License

This project is provided for **educational and reference purposes only**.

> Redistribution, modification, or commercial use is **strictly prohibited** without prior written permission.

© 2025 Kishwar Kumar – All rights reserved.
