# Raspberrypi_Yocto_Sensor_Node_ML_User_Space
The project uses **Linkersets** to manage modular initialization with high flexibility and complexity.
-  All modules registered via linkersets are automatically started during system initialization.
    ```bash
        /* register class to be auto-activated at startup (linkerset) */
        REGISTER_AUTO_INIT(CLI)
    ```
-  All CLI commands are also registered using linkersets, enabling dynamic command discovery and modular CLI handling.
    ```
        /* register CLI command with linkerset */
        CLI_COMMAND_REGISTER_BOTH("loglevel", Logging, setLevel, getLevel);
    ```
-  Any Queue created by module is also registered using linkerset, enabled dynamic discovery of queue by other modules.
    ```
        /* register queue with linkerset */
        REGISTER_QUEUE("TELNET_Q", Queue<>);
    ```

# Build Application
```bash
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application$ mkdir build
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application/build$ cmake ..
kkumar@DESKTOP-NK9HSKR:~/Raspberrypi_Yocto_Sensor_Node_ML_Kernel_User_Space/UserSpace/Application/build$ make -j4
```
