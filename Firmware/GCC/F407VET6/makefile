#*****************************************************************************
#Project names

PROJ_NAME=407_template
#PROJ_NAME_BOOTLOADER=205_template_boot_img

STARTUP_NAME=startup_stm32f407vetx
LINKER_SCRIPT=STM32F407VETX_FLASH.ld
#BOOTLOADER_LINKER_SCRIPT=STM32F205RCTX_FLASH_BOOTLOADERBIN.ld
OPENOCD_PROG_CFG:=/usr/share/openocd/scripts/interface/stlink-v2.cfg
OPENOCD_TARG_CFG:=/usr/share/openocd/scripts/target/stm32f4x.cfg


DIR_SRC_BOARD_MODELS:=Core/src/Board_models
DIR_SRC_MODEL:=F407




DIR_INC_CMSIS:=CMSIS/inc
DIR_INC_CMSIS_DEV:=CMSIS/inc

CSTANDART:=-std=gnu17
DEFSYMB:=-DSTM32 -DSTM32F4 -DSTM32F407VETx

CORTEX_M:=-mcpu=cortex-m4
FLOAT_M:=-mfloat-abi=soft
WARNING_M:=-Wall -Wextra -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion


#*****************************************************************************
#Output files
EXECUTABLE=$(PROJ_NAME).elf
BIN_IMAGE=$(PROJ_NAME).bin

EXECUTABLE_BOOTLOADER=$(PROJ_NAME_BOOTLOADER).elf
BIN_IMAGE_BOOTLOADER=$(PROJ_NAME_BOOTLOADER).bin

#*****************************************************************************
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
OBJSIZE=arm-none-eabi-size


#*****************************************************************************
DEBUG_DIR = ./Debug
RELEASE_DIR = ./Release

#*****************************************************************************
#************************ FINAL ASSMBLY **************************************
#*****************************************************************************
		
all:
	make subcore_board_models
	make subcore_bxcan
	make subcore_commands
	make subcore_dmaf10x
	make subcore_fdcan
	make subcore_flash_memchip
	make subcore_lin
	make subcore_spi
	make subcore_tim
	make subcore_usart
	make subcore_usb_cdc
	make subcore_vehicle_models
	make release
	make elf
	make list
	make hex
	make bin
	$(OBJSIZE) $(OBJ_ELF_RELEASE)

all-debug:
	make subcore_board_models-debug
	make subcore_bxcan-debug
	make subcore_commands-debug
	make subcore_dmaf10x-debug
	make subcore_fdcan-debug
	make subcore_flash_memchip-debug
	make subcore_lin-debug
	make subcore_spi-debug
	make subcore_tim-debug
	make subcore_usart-debug
	make subcore_usb_cdc-debug
	make subcore_vehicle_models-debug
	make debug
	make elf-debug
	make list-debug
	make hex-debug
	make bin-debug
	$(OBJSIZE) $(OBJ_ELF_DEBUG)
	
boot_bin: 
	+make bootloader
	
#*****************************************************************************
#************************ CMSIS OBJ ******************************************
#*****************************************************************************

#************************ CMSIS OBJ GENERAL **********************************
DIR_SRC_CMSIS:=CMSIS/src

INC_CMSIS := $(DIR_INC_CMSIS)/
SRC_CMSIS = $(wildcard $(DIR_SRC_CMSIS)/*.c)

#************************ CMSIS OBJ DEBUG ************************************
DIR_CMSIS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_CMSIS)
OBJ_CMSIS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_CMSIS)/*.c))

cmsis-debug: $(OBJ_CMSIS_DEBUG)
	
$(DIR_CMSIS_DEBUG)/%.o : $(DIR_SRC_CMSIS)/%.c
	mkdir -p $(DIR_CMSIS_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#************************ CMSIS OBJ RELEASE ************************************
DIR_CMSIS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_CMSIS)
OBJ_CMSIS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_CMSIS)/*.c))

cmsis: $(OBJ_CMSIS_RELEASE)
	
$(DIR_CMSIS_RELEASE)/%.o : $(DIR_SRC_CMSIS)/%.c
	mkdir -p $(DIR_CMSIS_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs $(FLOAT_M) -mthumb -o $@


#*****************************************************************************
#************************ LIBS OBJ *******************************************
#*****************************************************************************

#************************ LIBS OBJ GENERAL ***********************************
DIR_SRC_LIBS:=Libs/src
DIR_INC_LIBS:=Libs/inc

#Empty dir
INC_LIBS := $(DIR_INC_LIBS)/
SRC_LIBS = $(wildcard $(DIR_SRC_LIBS)/*.c)

#************************ LIBS OBJ DEBUG *************************************
DIR_LIBS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_LIBS)
# ./Debug/Libs/src
OBJ_LIBS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_LIBS)/*.c))
# ./Debug/Libs/src/*.o

libs-debug: $(OBJ_LIBS_DEBUG)

$(DIR_LIBS_DEBUG)/%.o : $(DIR_SRC_LIBS)/%.c
	mkdir -p $(DIR_LIBS_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB)-c -I"$(DIR_INC_LIBS)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections  -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#************************ LIBS OBJ RELEASE ***********************************
DIR_LIBS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_LIBS)
OBJ_LIBS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_LIBS)/*.c))

libs: $(OBJ_LIBS_RELEASE)

$(DIR_LIBS_RELEASE)/%.o : $(DIR_SRC_LIBS)/%.c
	mkdir -p $(DIR_LIBS_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs $(FLOAT_M) -mthumb -o $@


#*****************************************************************************
#************************ CORE OBJ *******************************************
#*****************************************************************************

#************************ CORE OBJ GENERAL ***********************************
DIR_SRC_CORE:=Core/src
DIR_INC_CORE:=Core/inc

#******************* SUBCORE DEVICE_MODELS DEBUG *****************************
DIR_BOARD_MODELS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)
OBJ_BOARD_MODELS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)/*.c))

subcore_board_models-debug: $(OBJ_BOARD_MODELS_DEBUG)

$(DIR_BOARD_MODELS_DEBUG)/%.o : $(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)/%.c
	mkdir -p $(DIR_BOARD_MODELS_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#****************** SUBCORE DEVICE_MODELS RELEASE ****************************
DIR_BOARD_MODELS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)
OBJ_BOARD_MODELS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)/*.c))

subcore_board_models: $(OBJ_BOARD_MODELS_RELEASE)

$(DIR_BOARD_MODELS_RELEASE)/%.o : $(DIR_SRC_BOARD_MODELS)/$(DIR_SRC_MODEL)/%.c
	mkdir -p $(DIR_BOARD_MODELS_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@





#*********************** SUBCORE BXCAN DEBUG *********************************
DIR_SRC_BXCAN:=Core/src/BxCAN

DIR_BXCAN_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_BXCAN)
OBJ_BXCAN_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_BXCAN)/*.c))

subcore_bxcan-debug: $(OBJ_BXCAN_DEBUG)

$(DIR_BXCAN_DEBUG)/%.o : $(DIR_SRC_BXCAN)/%.c
	mkdir -p $(DIR_BXCAN_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE BXCAN RELEASE *******************************
DIR_BXCAN_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_BXCAN)
OBJ_BXCAN_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_BXCAN)/*.c))

subcore_bxcan: $(OBJ_BXCAN_RELEASE)

$(DIR_BXCAN_RELEASE)/%.o : $(DIR_SRC_BXCAN)/%.c
	mkdir -p $(DIR_BXCAN_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@



#*********************** SUBCORE COMMANDS DEBUG *********************************
DIR_SRC_COMMANDS:=Core/src/Commands

DIR_COMMANDS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_COMMANDS)
OBJ_COMMANDS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_COMMANDS)/*.c))

subcore_commands-debug: $(OBJ_COMMANDS_DEBUG)

$(DIR_COMMANDS_DEBUG)/%.o : $(DIR_SRC_COMMANDS)/%.c
	mkdir -p $(DIR_COMMANDS_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE COMMANDS RELEASE *******************************
DIR_COMMANDS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_COMMANDS)
OBJ_COMMANDS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_COMMANDS)/*.c))

subcore_commands: $(OBJ_COMMANDS_RELEASE)

$(DIR_COMMANDS_RELEASE)/%.o : $(DIR_SRC_COMMANDS)/%.c
	mkdir -p $(DIR_COMMANDS_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@
	
	




#*********************** SUBCORE DMAF10X DEBUG *********************************
DIR_SRC_DMAF10X:=Core/src/DMAF10x

DIR_DMAF10X_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_DMAF10X)
OBJ_DMAF10X_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_DMAF10X)/*.c))

subcore_dmaf10x-debug: $(OBJ_DMAF10X_DEBUG)

$(DIR_DMAF10X_DEBUG)/%.o : $(DIR_SRC_DMAF10X)/%.c
	mkdir -p $(DIR_DMAF10X_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE DMAF10X RELEASE *******************************
DIR_DMAF10X_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_DMAF10X)
OBJ_DMAF10X_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_DMAF10X)/*.c))

subcore_dmaf10x: $(OBJ_DMAF10X_RELEASE)

$(DIR_DMAF10X_RELEASE)/%.o : $(DIR_SRC_DMAF10X)/%.c
	mkdir -p $(DIR_DMAF10X_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@



#*********************** SUBCORE FDCAN DEBUG *********************************
DIR_SRC_FDCAN:=Core/src/FDCAN

DIR_FDCAN_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_FDCAN)
OBJ_FDCAN_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_FDCAN)/*.c))

subcore_fdcan-debug: $(OBJ_FDCAN_DEBUG)

$(DIR_FDCAN_DEBUG)/%.o : $(DIR_SRC_FDCAN)/%.c
	mkdir -p $(DIR_FDCAN_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE FDCAN RELEASE *******************************
DIR_FDCAN_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_FDCAN)
OBJ_FDCAN_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_FDCAN)/*.c))

subcore_fdcan: $(OBJ_FDCAN_RELEASE)

$(DIR_FDCAN_RELEASE)/%.o : $(DIR_SRC_FDCAN)/%.c
	mkdir -p $(DIR_FDCAN_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@




#*********************** SUBCORE FLASH_MEMCHIP DEBUG *********************************
DIR_SRC_FLASH_MEMCHIP:=Core/src/Flash_memchip

DIR_FLASH_MEMCHIP_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_FLASH_MEMCHIP)
OBJ_FLASH_MEMCHIP_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_FLASH_MEMCHIP)/*.c))

subcore_flash_memchip-debug: $(OBJ_FLASH_MEMCHIP_DEBUG)

$(DIR_FLASH_MEMCHIP_DEBUG)/%.o : $(DIR_SRC_FLASH_MEMCHIP)/%.c
	mkdir -p $(DIR_FLASH_MEMCHIP_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE FLASH_MEMCHIP RELEASE *******************************
DIR_FLASH_MEMCHIP_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_FLASH_MEMCHIP)
OBJ_FLASH_MEMCHIP_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_FLASH_MEMCHIP)/*.c))

subcore_flash_memchip: $(OBJ_FLASH_MEMCHIP_RELEASE)

$(DIR_FLASH_MEMCHIP_RELEASE)/%.o : $(DIR_SRC_FLASH_MEMCHIP)/%.c
	mkdir -p $(DIR_FLASH_MEMCHIP_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@



#*********************** SUBCORE LIN DEBUG *********************************
DIR_SRC_LIN:=Core/src/LIN

DIR_LIN_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_LIN)
OBJ_LIN_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_LIN)/*.c))

subcore_lin-debug: $(OBJ_LIN_DEBUG)

$(DIR_LIN_DEBUG)/%.o : $(DIR_SRC_LIN)/%.c
	mkdir -p $(DIR_LIN_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE LIN RELEASE *******************************
DIR_LIN_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_LIN)
OBJ_LIN_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_LIN)/*.c))

subcore_lin: $(OBJ_LIN_RELEASE)

$(DIR_LIN_RELEASE)/%.o : $(DIR_SRC_LIN)/%.c
	mkdir -p $(DIR_LIN_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@


#*********************** SUBCORE SPI DEBUG *********************************
DIR_SRC_SPI:=Core/src/SPI

DIR_SPI_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_SPI)
OBJ_SPI_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_SPI)/*.c))

subcore_spi-debug: $(OBJ_SPI_DEBUG)

$(DIR_SPI_DEBUG)/%.o : $(DIR_SRC_SPI)/%.c
	mkdir -p $(DIR_SPI_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE SPI RELEASE *******************************
DIR_SPI_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_SPI)
OBJ_SPI_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_SPI)/*.c))

subcore_spi: $(OBJ_SPI_RELEASE)

$(DIR_SPI_RELEASE)/%.o : $(DIR_SRC_SPI)/%.c
	mkdir -p $(DIR_SPI_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@




#*********************** SUBCORE TIM DEBUG *********************************
DIR_SRC_TIM:=Core/src/TIM

DIR_TIM_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_TIM)
OBJ_TIM_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_TIM)/*.c))

subcore_tim-debug: $(OBJ_TIM_DEBUG)

$(DIR_TIM_DEBUG)/%.o : $(DIR_SRC_TIM)/%.c
	mkdir -p $(DIR_TIM_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE TIM RELEASE *******************************
DIR_TIM_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_TIM)
OBJ_TIM_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_TIM)/*.c))

subcore_tim: $(OBJ_TIM_RELEASE)

$(DIR_TIM_RELEASE)/%.o : $(DIR_SRC_TIM)/%.c
	mkdir -p $(DIR_TIM_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@




#*********************** SUBCORE USART DEBUG *********************************
DIR_SRC_USART:=Core/src/USART

DIR_USART_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_USART)
OBJ_USART_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_USART)/*.c))

subcore_usart-debug: $(OBJ_USART_DEBUG)

$(DIR_USART_DEBUG)/%.o : $(DIR_SRC_USART)/%.c
	mkdir -p $(DIR_USART_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE USART RELEASE *******************************
DIR_USART_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_USART)
OBJ_USART_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_USART)/*.c))

subcore_usart: $(OBJ_USART_RELEASE)

$(DIR_USART_RELEASE)/%.o : $(DIR_SRC_USART)/%.c
	mkdir -p $(DIR_USART_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@



#*********************** SUBCORE USB_CDC DEBUG *********************************
DIR_SRC_USB_CDC:=Core/src/USB_CDC

DIR_USB_CDC_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_USB_CDC)
OBJ_USB_CDC_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_USB_CDC)/*.c))

subcore_usb_cdc-debug: $(OBJ_USB_CDC_DEBUG)

$(DIR_USB_CDC_DEBUG)/%.o : $(DIR_SRC_USB_CDC)/%.c
	mkdir -p $(DIR_USB_CDC_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE USB_CDC RELEASE *******************************
DIR_USB_CDC_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_USB_CDC)
OBJ_USB_CDC_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_USB_CDC)/*.c))

subcore_usb_cdc: $(OBJ_USB_CDC_RELEASE)

$(DIR_USB_CDC_RELEASE)/%.o : $(DIR_SRC_USB_CDC)/%.c
	mkdir -p $(DIR_USB_CDC_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@
	


#*********************** SUBCORE VEHICLE_MODELS DEBUG *********************************
DIR_SRC_VEHICLE_MODELS:=Core/src/Vehicle_models

DIR_VEHICLE_MODELS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_VEHICLE_MODELS)
OBJ_VEHICLE_MODELS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_VEHICLE_MODELS)/*.c))

subcore_vehicle_models-debug: $(OBJ_VEHICLE_MODELS_DEBUG)

$(DIR_VEHICLE_MODELS_DEBUG)/%.o : $(DIR_SRC_VEHICLE_MODELS)/%.c
	mkdir -p $(DIR_VEHICLE_MODELS_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#*********************** SUBCORE VEHICLE_MODELS RELEASE *******************************
DIR_VEHICLE_MODELS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_VEHICLE_MODELS)
OBJ_VEHICLE_MODELS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_VEHICLE_MODELS)/*.c))

subcore_vehicle_models: $(OBJ_VEHICLE_MODELS_RELEASE)

$(DIR_VEHICLE_MODELS_RELEASE)/%.o : $(DIR_SRC_VEHICLE_MODELS)/%.c
	mkdir -p $(DIR_VEHICLE_MODELS_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@
	








#************************ CORE OBJ DEBUG *************************************
DIR_CORE_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_CORE)
OBJ_CORE_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_CORE)/*.c))

core-debug: $(OBJ_CORE_DEBUG)

$(DIR_CORE_DEBUG)/%.o : $(DIR_SRC_CORE)/%.c
	mkdir -p $(DIR_CORE_DEBUG)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections $(WARNING_M) -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $@

#************************ CORE OBJ RELEASE ***********************************
DIR_CORE_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_CORE)
OBJ_CORE_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_CORE)/*.c))

core: $(OBJ_CORE_RELEASE)

$(DIR_CORE_RELEASE)/%.o : $(DIR_SRC_CORE)/%.c
	mkdir -p $(DIR_CORE_RELEASE)
	$(CC) $^ $(CORTEX_M) $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections $(WARNING_M) --specs=nano.specs $(FLOAT_M) -mthumb -o $@


#*****************************************************************************
#************************ STARTUP OBJ ****************************************
#*****************************************************************************

#************************ STARTUP OBJ GENERAL ********************************
DIR_SRC_STARTUP:=Startup

STARTUP_SRC:=$(DIR_SRC_STARTUP)/$(STARTUP_NAME).s

#************************ STARTUP OBJ DEBUG ***********************************
DIR_STARTUP_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_STARTUP)
OBJ_STARTUP_DEBUG := $(DIR_STARTUP_DEBUG)/$(STARTUP_NAME).o

startup-debug: $(OBJ_STARTUP_DEBUG)

$(OBJ_STARTUP_DEBUG) : $(STARTUP_SRC)
	mkdir -p $(DIR_STARTUP_DEBUG)	
	$(CC) $^ -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $(DIR_STARTUP_DEBUG)/$(STARTUP_NAME).o $(DIR_SRC_STARTUP)/$(STARTUP_NAME).s
	
#************************ STARTUP OBJ RELEASE ********************************
DIR_STARTUP_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_STARTUP)
OBJ_STARTUP_RELEASE := $(DIR_STARTUP_RELEASE)/$(STARTUP_NAME).o

startup: $(OBJ_STARTUP_RELEASE)

$(OBJ_STARTUP_RELEASE) : $(STARTUP_SRC)
	mkdir -p $(DIR_STARTUP_RELEASE)	
	$(CC) $^ -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs $(FLOAT_M) -mthumb -o $(DIR_STARTUP_RELEASE)/$(STARTUP_NAME).o $(DIR_SRC_STARTUP)/$(STARTUP_NAME).s


#*****************************************************************************
#************************ BOOTLOADER OBJ *************************************
#*****************************************************************************

#********************* BOOTLOADER RELEASE ************************************

OBJ_RELEASE_BOOTLOADER+= $(RELEASE_DIR)/$(EXECUTABLE)
bootloader: $(OBJ_STARTUP_RELEASE) $(OBJ_CMSIS_RELEASE) $(OBJ_CORE_RELEASE) $(OBJ_LIBS_RELEASE)
	$(CC) -o $(RELEASE_DIR)/205_template.elf $(OBJ_STARTUP_RELEASE) $(OBJ_CMSIS_RELEASE) $(OBJ_CORE_RELEASE) $(OBJ_LIBS_RELEASE) $(CORTEX_M) -T"./$(DIR_SRC_STARTUP)/$(BOOTLOADER_LINKER_SCRIPT)" --specs=nosys.specs -Wl,-Map=$(RELEASE_DIR)/205_template.map -Wl,--gc-sections -static --specs=nano.specs $(FLOAT_M) -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	$(OBJSIZE)   $(RELEASE_DIR)/205_template.elf
	$(OBJDUMP) -h -S  $(RELEASE_DIR)/205_template.elf  > $(RELEASE_DIR)/205_template.list
	$(OBJCOPY) -O ihex  $(RELEASE_DIR)/205_template.elf  $(RELEASE_DIR)/205_template.hex
	$(OBJCOPY) -O binary  $(RELEASE_DIR)/205_template.elf  $(RELEASE_DIR)/205_template.bin	

#*****************************************************************************
#************************ ELF OBJ ********************************************
#*****************************************************************************

DIR_SRC_STARTUP:=Startup

STARTUP_SRC:=$(DIR_SRC_STARTUP)/$(STARTUP_NAME).s

#**************************** ELF DEBUG **************************************
OBJ_ELF_DEBUG := $(DEBUG_DIR)/$(EXECUTABLE)
elf-debug: $(OBJ_ELF_DEBUG)

$(OBJ_ELF_DEBUG) : $(STARTUP_SRC) $(DIR_INC_CORE) $(DIR_INC_CMSIS) $(DIR_INC_CMSIS_DEV) $(OBJ_BOARD_MODELS_DEBUG) $(OBJ_BXCAN_DEBUG) $(OBJ_COMMANDS_DEBUG) $(OBJ_DMAF10X_DEBUG) $(OBJ_FDCAN_DEBUG) $(OBJ_FLASH_MEMCHIP_DEBUG) $(OBJ_LIN_DEBUG) $(OBJ_SPI_DEBUG) $(OBJ_TIM_DEBUG) $(OBJ_USART_DEBUG) $(OBJ_USB_CDC_DEBUG) $(OBJ_VEHICLE_MODELS_DEBUG)
	mkdir -p $(DEBUG_DIR)
	$(CC) -o $(OBJ_ELF_DEBUG) $(OBJ_CORE_DEBUG) $(OBJ_BOARD_MODELS_DEBUG) $(OBJ_BXCAN_DEBUG) $(OBJ_COMMANDS_DEBUG) $(OBJ_DMAF10X_DEBUG) $(OBJ_FDCAN_DEBUG) $(OBJ_FLASH_MEMCHIP_DEBUG) $(OBJ_LIN_DEBUG) $(OBJ_SPI_DEBUG) $(OBJ_TIM_DEBUG) $(OBJ_USART_DEBUG) $(OBJ_USB_CDC_DEBUG) $(OBJ_VEHICLE_MODELS_DEBUG) $(OBJ_LIBS_DEBUG) $(OBJ_CMSIS_DEBUG) $(OBJ_STARTUP_DEBUG) $(CORTEX_M) -T $(DIR_SRC_STARTUP)/$(LINKER_SCRIPT) --specs=nosys.specs -Wl,-Map=$(DEBUG_DIR)/$(PROJ_NAME).map -Wl,--gc-sections -static --specs=nano.specs $(FLOAT_M) -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

LIST_DEBUG:= $(DEBUG_DIR)/$(PROJ_NAME).list
list-debug: $(OBJ_ELF_DEBUG)
	$(OBJDUMP) -h -S  $(OBJ_ELF_DEBUG)  >  $(LIST_DEBUG)
	
HEX_DEBUG:= $(DEBUG_DIR)/$(PROJ_NAME).hex	
hex-debug: $(OBJ_ELF_DEBUG)
	$(OBJCOPY) -O ihex  $(OBJ_ELF_DEBUG)  $(HEX_DEBUG)
	
BIN_DEBUG:= $(DEBUG_DIR)/$(BIN_IMAGE)	
bin-debug: $(OBJ_ELF_DEBUG)
	$(OBJCOPY) -O binary  $(OBJ_ELF_DEBUG)  $(BIN_DEBUG)
	
#**************************** ELF RELEASE ************************************
OBJ_ELF_RELEASE := $(RELEASE_DIR)/$(EXECUTABLE)
elf: $(OBJ_ELF_RELEASE)

$(OBJ_ELF_RELEASE) : $(STARTUP_SRC) $(DIR_INC_CORE) $(DIR_INC_CMSIS) $(DIR_INC_CMSIS_DEV) $(OBJ_BOARD_MODELS_RELEASE) $(OBJ_BXCAN_RELEASE) $(OBJ_COMMANDS_RELEASE) $(OBJ_DMAF10X_RELEASE) $(OBJ_FDCAN_RELEASE) $(OBJ_FLASH_MEMCHIP_RELEASE) $(OBJ_LIN_RELEASE) $(OBJ_SPI_RELEASE) $(OBJ_TIM_RELEASE) $(OBJ_USART_RELEASE) $(OBJ_USB_CDC_RELEASE) $(OBJ_VEHICLE_MODELS_RELEASE) 
	mkdir -p $(RELEASE_DIR)
	$(CC) -o $(OBJ_ELF_RELEASE) $(OBJ_CORE_RELEASE) $(OBJ_BOARD_MODELS_RELEASE) $(OBJ_BXCAN_RELEASE) $(OBJ_COMMANDS_RELEASE) $(OBJ_DMAF10X_RELEASE) $(OBJ_FDCAN_RELEASE) $(OBJ_FLASH_MEMCHIP_RELEASE) $(OBJ_LIN_RELEASE) $(OBJ_SPI_RELEASE) $(OBJ_TIM_RELEASE) $(OBJ_USART_RELEASE) $(OBJ_USB_CDC_RELEASE) $(OBJ_VEHICLE_MODELS_RELEASE) $(OBJ_LIBS_RELEASE) $(OBJ_CMSIS_RELEASE) $(OBJ_STARTUP_RELEASE) $(CORTEX_M) -T $(DIR_SRC_STARTUP)/$(LINKER_SCRIPT) --specs=nosys.specs -Wl,-Map=$(RELEASE_DIR)/$(PROJ_NAME).map -Wl,--gc-sections -static --specs=nano.specs $(FLOAT_M) -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

LIST_RELEASE:= $(RELEASE_DIR)/$(PROJ_NAME).list
list: $(OBJ_ELF_RELEASE)
	$(OBJDUMP) -h -S  $(OBJ_ELF_RELEASE)  > $(LIST_RELEASE)
	
HEX_RELEASE:= $(RELEASE_DIR)/$(PROJ_NAME).hex	
hex: $(OBJ_ELF_RELEASE)
	$(OBJCOPY) -O ihex  $(OBJ_ELF_RELEASE)  $(HEX_RELEASE)
	
BIN_RELEASE:= $(RELEASE_DIR)/$(BIN_IMAGE)	
bin: $(OBJ_ELF_RELEASE)
	$(OBJCOPY) -O binary  $(OBJ_ELF_RELEASE)  $(BIN_RELEASE)

#*****************************************************************************
#************************ FINAL ASSMBLY **************************************
#*****************************************************************************

debug: $(OBJ_CORE_DEBUG) $(OBJ_LIBS_DEBUG) $(OBJ_CMSIS_DEBUG) $(OBJ_STARTUP_DEBUG)
release: $(OBJ_CORE_RELEASE) $(OBJ_LIBS_RELEASE) $(OBJ_CMSIS_RELEASE) $(OBJ_STARTUP_RELEASE)
	
col:="
flash:
	if [ -e $(HEX_RELEASE) ]; then sudo openocd -f $(OPENOCD_PROG_CFG) -f $(OPENOCD_TARG_CFG) -c $(col)init; reset halt; flash write_image erase $(HEX_RELEASE); $(col)$(col)reset; exit$(col); \
	elif [ -e $(HEX_DEBUG) ]; then sudo openocd -f $(OPENOCD_PROG_CFG) -f $(OPENOCD_TARG_CFG) -c $(col)init; reset halt; flash write_image erase $(HEX_DEBUG); $(col)$(col)reset; exit$(col); \
	else echo "********* No file to load *********"; \
	fi

clean-obj:
	rm -rf $(DIR_CMSIS_DEBUG)/*.o
	rm -rf $(DIR_CMSIS_DEBUG)/*.su
	rm -rf $(DIR_CMSIS_DEBUG)/*d
	rm -rf $(DIR_CMSIS_RELEASE)/*.o
	rm -rf $(DIR_CMSIS_RELEASE)/*.su
	rm -rf $(DIR_CMSIS_RELEASE)/*d
		
	rm -rf $(DIR_LIBS_DEBUG)/*.o
	rm -rf $(DIR_LIBS_DEBUG)/*.su
	rm -rf $(DIR_LIBS_DEBUG)/*d	
	rm -rf $(DIR_LIBS_RELEASE)/*.o
	rm -rf $(DIR_LIBS_RELEASE)/*.su
	rm -rf $(DIR_LIBS_RELEASE)/*d	
	
	rm -rf $(DIR_CORE_DEBUG)/*.o
	rm -rf $(DIR_CORE_DEBUG)/*.su
	rm -rf $(DIR_CORE_DEBUG)/*d	
	rm -rf $(DIR_CORE_RELEASE)/*.o
	rm -rf $(DIR_CORE_RELEASE)/*.su
	rm -rf $(DIR_CORE_RELEASE)/*d	
	
	rm -rf $(DIR_STARTUP_DEBUG)/*.o
	rm -rf $(DIR_STARTUP_DEBUG)/*.d
	rm -rf $(DIR_STARTUP_RELEASE)/*.o
	rm -rf $(DIR_STARTUP_RELEASE)/*.d
	
clean:
	make clean-obj
	rm -rf $(DEBUG_DIR)/$(EXECUTABLE)
	rm -rf $(DEBUG_DIR)/$(PROJ_NAME).map
	rm -rf $(LIST_DEBUG)
	rm -rf $(HEX_DEBUG)
	rm -rf $(BIN_DEBUG)
	
	rm -rf $(RELEASE_DIR)/$(EXECUTABLE)
	rm -rf $(RELEASE_DIR)/$(PROJ_NAME).map
	rm -rf $(LIST_RELEASE)
	rm -rf $(HEX_RELEASE)
	rm -rf $(BIN_RELEASE)
	rm -rf $(DEBUG_DIR)
	rm -rf $(RELEASE_DIR)
	
echo:
	@echo $(DIR_CMSIS_DEBUG)/*.o
	@echo $(DIR_CMSIS_DEBUG)/*.su
	@echo $(DIR_CMSIS_DEBUG)/*d
	@echo $(DIR_CMSIS_RELEASE)/*.o
	@echo $(DIR_CMSIS_RELEASE)/*.su
	@echo $(DIR_CMSIS_RELEASE)/*d
		
	@echo $(DIR_LIBS_DEBUG)/*.o
	@echo $(DIR_LIBS_DEBUG)/*.su
	@echo $(DIR_LIBS_DEBUG)/*d	
	@echo $(DIR_LIBS_RELEASE)/*.o
	@echo $(DIR_LIBS_RELEASE)/*.su
	@echo $(DIR_LIBS_RELEASE)/*d	
	
	@echo $(DIR_CORE_DEBUG)/*.o
	@echo $(DIR_CORE_DEBUG)/*.su
	@echo $(DIR_CORE_DEBUG)/*d	
	@echo $(DIR_CORE_RELEASE)/*.o
	@echo $(DIR_CORE_RELEASE)/*.su
	@echo $(DIR_CORE_RELEASE)/*d	
	
	@echo $(DIR_STARTUP_DEBUG)/*.o
	@echo $(DIR_STARTUP_DEBUG)/*.d
	@echo $(DIR_STARTUP_RELEASE)/*.o
	@echo $(DIR_STARTUP_RELEASE)/*.d


	
.PHONY: echo clean clean-obj cmsis-debug libs-debug core-debug startup-debug list-debug bin-debug elf-debug debug cmsis libs core startup list bin elf debug all-debug all flash
