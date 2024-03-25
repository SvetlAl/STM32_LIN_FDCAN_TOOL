# STM32F105 STM32F205 STM32F407 STM32H730
LIN, FD-CAN bus Scanner/Gateway/filter/data_override/trace editor/multitool based on STM32, Qt. Works with multiple antitheft devices.

**Current status.**
Usage example here:
https://www.youtube.com/watch?v=TV64RHSr5Tw&lc=

Interface overview:
https://youtu.be/wPPCQm3Kelo

Now I'm fixing minor bugs and preparing CAN FD support.


**Work explanation.**
This firmware and interface template is designed to handle a CAN bus gateway installed in between two ECU's.

USB CDC interface (implemented on PC or Android) allows to override and filter data coming BOTH ways.

CAN-Scanner function allows to split a CAN network and display all the data along with affiliation to CAN1 or CAN2. So when two ECU's are exchanging data, both data and direction are displayed.

CAN-injection function allows to make a CAN message trace and play it into network.

![Work_explanation](Docs/Work_explanation.png)

**Hardware requirements.**
The hardware implementation is based on STM32 + 2 CAN trancievers + USB FS + SPI Memory chip (MX25L323 or similar).

The code already has **9 hardware configuration**. Their pinout explanation and clocking can be found in Boards_Docs directory.

The bus terminators are optionally installed if needed.

![STM32F105_clock](Docs/Clock_Presets/105_schema.jpg)
![A possible configuration](Docs/Hardware_Presets/DEVICE_2CAN_TJA1042.png)

**Firmware.**
Optional bootloader is designed to load a bin image from 0x030000 of external memory chip and a bin image size from 0x03FFFC. The main application FLASH address is 0x8004000.

**project_settings.h**
project_settings.h - is a main configuration file.
Edit *project_settings.h* CommentUncomment  the hardware preset and Environment (**MDK-ARM** or **GCC**).
For example, if you want to use STM32F407 devboard, uncomment #define DEVICE_DEVBOARD_F407VET_A and comment all other presets

If **MDK_ARM**, open 105_template.uvprojx or 205_template.uvprojx.

If **GCC**, use a makefile script
```
make all -j 8

(make boot_bin) only for bootloader

(make flash)  *see programmer conf in the makefile.

make clean
```

**User Interface.**
Implemented in Qt 6.50. The sources and compiled versions can be found in qt_interface folder.

Android USB implementation is forked from https://github.com/VanThanBK/QtAndroid-UsbSerial
![FD_CAN](Docs/fdcan.png)
![2 way Scanner](Docs/can_monitor.png)
![can_trace](Docs/can_trace.png)
![device_modes](Docs/device_modes.png)
![can_data_override](Docs/can_data_override.png)
![can_data_discard](Docs/can_data_discard.png)
![SPI memory chip monitor](Docs/memory_monitor.png)
![play_trace](Docs/play_trace.png)
![settings](Docs/settings.png)

**Important!!!**
Before you start, make sure the memory chip is completely erased. (Connect to device using a COM-port terminal, then send @S00000007@E command).

It's recommended to set max. transmission chunks for RX and TX to 256 in the app settings.

Some device modes (like gateway and cdc injection) may be conflicting, so use only the necessary modes.

If CAN override filter is not working, check if calibrator mode is on. 

**CAN Scanner limitations**
In Android version (USB OTG CDC) dataflow capability may be not enough to handle an excessive CAN-traffic. In this case use a hardware filter to set a monitored range on a firmware side.
![hw_filter](Docs/hw_filter.png)

**CAN injection limitations**
There are two trace injection modes: 
- from the memory chip (not tested, not included by default)

- from the data coming via COM-Port:
a trace is supposed to be played according to the timestamps, but maximum real-time payload is 4 messages with 10.0 msec period at once. This is due to USB CDC flowrate limitation.

If "auto adjust" was set, a trace play would be automaticaly slowed down to be able to play all trace data.
Alternatively, a fixed threshold can be set.
This function is not recommended for use with Android.
![hw_filter](Docs/inj_threshold.png)

**General Android limitations**
Android support here is not native and should not be used with excessive USB data traffic. Slow down transmission or use hardware filters id needed.



**LIN bus support**
LIN bus is supported with 4 modes:
*Device*: any custom logic implemented in void lin_device_master_tx(void); void lin_device_slave_rx(void);
*Gateway*: split a LIN bus and install a gateway in between Master output. 
Then, use these two modes:
*Filter*: 2 fiter available - MISO and MOSI respectively.
*Scanner*: similar to CAN scanner, but with reduced features.

![hw_filter](Docs/LIN_monitor.png)
![hw_filter](Docs/LIN_trace.png)
![hw_filter](Docs/LIN_settings.png)

The only hardware configuration, that supports LIN is DEVICE_2CAN
![LIN hardware config](Docs/Hardware_Presets/DEVICE_2CAN.png)


**Credits**
The Android com-port implementation made by VanThanBK: https://github.com/VanThanBK/QtAndroid-UsbSerial


