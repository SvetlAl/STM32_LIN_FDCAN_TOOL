# STM32F105_205_2CAN_gateway_scanner_filter
CAN bus Scanner/Gateway/filter/data_override based on STM32, Qt. Works with Starline 2CAN, Sigma and similar


**Work explanation.**
This firmware and interface template is designed to handle a CAN bus gateway installed in between two ECU's or a CAN network split into two networks.

USB CDC interface (implemented on PC or Android) allows to override and filter data coming BOTH ways.

CAN-Scanner function allows to split a CAN network and display all the data along with affiliation to CAN1 or CAN2. So when two ECU's are exchanging data, this can be seen for sure, what data and what direction is coming.

CAN-injection function allows to make a CAN message trace and play it into network. this feature is still to be developed. The data is injected at max speed, no additional configuration provided.

![Work_explanation](Docs/Work_explanation.png)

**Hardware requirements.**
The hardware implementation is based on STM32F105205 + 2 CAN trancievers + USB FS + SPI Memory chip (MX25L323 or similar).

The code already has **6 hardware configuration**. Their pinout explanation and clocking can be found in Doc directory.

The bus terminators are optionally installed if needed.

![STM32F105_clock](Docs/Clock_Presets/105_schema.jpg)
![A possible configuration](Docs/Hardware_Presets/DEVICE_2CAN_TJA1042.png)

**Firmware.**
Optional bootloader is designed to load a bin image from 0x030000 of external memory chip and a bin image size from 0x03FFFC. The main application FLASH address is 0x8004000.

Edit *device_model.h* CommentUncomment  the hardware preset and Environment (**MDK-ARM** or **GCC**).

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
![2 way Scanner](Docs/can_monitor.png)
![can_trace](Docs/can_trace.png)
![device_modes](Docs/device_modes.png)
![can_data_override](Docs/can_data_override.png)
![can_data_discard](Docs/can_data_discard.png)
![SPI memory chip monitor](Docs/memory_monitor.png)
![play_trace](Docs/play_trace.png)
![settings](Docs/settings.png)

