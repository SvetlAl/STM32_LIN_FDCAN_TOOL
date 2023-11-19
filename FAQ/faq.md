- Where do you find this App?

Right here, you can find 3 versions:
https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/tree/master/qt_interface/compiled

- How do you load this App on your android?
Android devices are different from one to another. You should read the manual for exact your device. In general case, you allow apk installation in the settings, then you download an .apk file, then press "install".


- What device are you using as the interface to control the instrument cluster?
This was my idea in the first place:
You don't have to assemble a device by yourself, just minimum soldering.
When I'd been stripping for parts a lot of aftermarket automotive electronics (like car alarms, aftermarket heat systems, CAN-gateways, etc), I found a lot of modules, that meet the requirements.
You just find a module and reprogramm it. 

Alternatively you can assemble a device by yourself.
Here in https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/tree/master/FAQ there are photos of some modules I use more often. All of them were found in aftermarket automotive electronics, extracted and reprogrammed.

Supported MK are STM32F105, F205.
Soon STM32H730 will be added as well.

-Will STM32F407VET6 work as an alternative to STM32F105/205?
Yes, 99% of the code would be the same.
But you need to make some adaptations: mostly clocking and FPU.

If you using a test board like this https://github.com/SvetlAl/STM32_FS_USB_CDC_device_CMSIS/blob/master/STM32F407_sloppy_example/modul-na-osnove-stm32f407vet6_s4.jpg
I would solder in 2 CAN tranceiver PCBs:
https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/blob/master/FAQ/IMG_20231119_170906.jpg
https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/blob/master/FAQ/IMG_20231119_170852.jpg
And then adapt the code for a new configuration.
Memory chip here is VINBOND 25. I think, it's completetly compartible with MX25L323. Otherwise it is easy to replace it with MX25L323.



- 2 CAN transceivers (which ones?)
- USB FS  i.e. usb cable
- SPI Memory chip (MX25L323 or similar). (How to connected all together?)
- How are the required components configured--- physically?
- What kind of CAN transceivers; USB FS; SPI Memory chip?

A short andwer:
any CAN tranceivers with 500 kb/s support (just pay attention to STB pins),
any SPI Memory (most of them have similar commands). If the commands are different, edit this file https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/blob/master/stm32/Keil/105_205_template/Core/inc/flash_mem_chip_spi.h

I haven't drawn full schemas for my devices, but you can see the MK pin assignment here:
https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/tree/master/Docs/Hardware_Presets
My idea was, that you take a pre-built module and you don't need a detailed schema, you need only microcontroller pin assignment.

I have 6 pre-configures hardwares setup in the code. This can be used as a reference/example.
1. You find a pin connection, that fits your device in https://github.com/SvetlAl/STM32F105_205_2_CAN_LIN_gateway_scanner_filter/tree/master/Docs/Hardware_Presets
2. In the "device_model.h" file you uncomment a corresponding device preset. This main setting branches into multiple defines in other files, that specify a pinout, memory chip model and others.
3. Alternatively you can add your own hardware config. Use the pre-configs as example.



How much to send me the plug and play setup? (device, usb cable, downloadable App. )
The app is free, all the code and compiled GUI are here.
If you don't have opportunity to find a suitable hardware, theoretically I can send you some pieces scrapped from used electronics. Prepare and test, but without any warranty, because this is a used third party product.
svetlal@outlook.com
