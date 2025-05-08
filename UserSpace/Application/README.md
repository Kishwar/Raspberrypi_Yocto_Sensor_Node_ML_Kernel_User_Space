# EmbeddedApp – User Space Application for Raspberry Pi Sensor Node

This component is part of a modular embedded system targeting Raspberry Pi.
It focuses on the **user space application**, which manages real-time data from various kernel-space sensor drivers, performs logic and control, and integrates a lightweight machine learning model.

A key feature of this application is its use of **sophisticated linker sets** to provide a flexible and dynamically extensible architecture.

---

## ⚙️ Architecture Overview

The application uses **linker sets** to automatically register and initialize components at runtime. This mechanism enables modular design, eliminates manual dependency wiring, and improves scalability.

### 🔁 Automatic Module Initialization

Modules can register themselves for auto-start at runtime using:

```cpp
/* Register class to be auto-activated at startup using linker set */
REGISTER_AUTO_INIT(CLI)
```

### 💡 Dynamic CLI Command Registration

Each CLI command is modular and registered independently, enabling runtime discovery:

```cpp
/* Register CLI command with linker set */
CLI_COMMAND_REGISTER_BOTH("loglevel", Logging, setLevel, getLevel);
```

### 📬 Cross-Module Queue Discovery

Modules can register their queues using linker sets, allowing other modules to discover and use them without tight coupling:

```cpp
/* Register queue with linker set */
REGISTER_QUEUE("TELNET_Q", Queue<>);
```

---

## 🧱 Project Structure

```
UserSpace/Application/
├── core/          # Template utilities (header-only)
├── services/      # Modular components (CLI, logging, telnet, etc.)
├── main/          # Entry point of the application
├── linkerset.ld   # Custom linker script to handle linker sections
├── CMakeLists.txt # Top-level build configuration
└── EmbeddedApp.service  # systemd service file
```

---

## 🧪 Build Instructions

### 1. Source the Yocto Toolchain

Make sure you have Yocto SDK installed and run:

```bash
source /opt/poky/4.0.21/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
```

### 2. Build the Application

```bash
cd UserSpace/Application
mkdir build
cd build
cmake ..
make -j$(nproc)
```

The final binary will be created here:

```
build/binaries/EmbeddedApp
```

---

## 🔄 Deploy & Run with systemd

To auto-run `EmbeddedApp` on boot:

### Step 1: Move Binary to Home

```bash
scp build/binaries/EmbeddedApp <root>@<192.168.178.98>:/home/
ssh <root>@<192.168.178.98>
chmod +x /home/EmbeddedApp
```

### Step 2: Create the systemd Service

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

### Step 3: Enable & Start the Service

```bash
sudo systemctl daemon-reexec
sudo systemctl daemon-reload
sudo systemctl enable EmbeddedApp.service
sudo systemctl start EmbeddedApp.service
```

### Step 4: Check Status and Logs

```bash
systemctl status EmbeddedApp.service
journalctl -u EmbeddedApp.service
```

---

## 💡 Why Linker Sets?

Linker sets provide a highly modular and dynamic architecture. By using special linker sections and macros, components can:

- Register themselves without central references
- Extend CLI or functionality without modifying a main registry
- Enable dynamic discovery and decoupling

This is especially useful in embedded systems where memory layout, performance, and modularity matter.

---

## 📄 License

This project is made available **for educational and reference purposes only**.

> Redistribution, modification, or commercial use is **strictly prohibited** without prior written permission from the author.

© 2025 Kishwar Kumar – All rights reserved.

---

## 📫 Contact

Feel free to open an issue or reach out via GitHub if you have questions or suggestions.
