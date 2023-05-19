#*****************************************************************************
#Project names

PROJ_NAME=205_template

STARTUP_NAME=startup_stm32f205rctx
LINKER_SCRIPT=STM32F205RCTX_FLASH.ld
#BOOTLOADER_LINKER_SCRIPT=STM32F205RCTX_FLASH_BOOTLOADERBIN.ld
OPENOCD_PROG_CFG:=/usr/share/openocd/scripts/interface/stlink-v2.cfg
OPENOCD_TARG_CFG:=/usr/share/openocd/scripts/target/stm32f2x.cfg
CSTANDART:=-std=gnu17
DEFSYMB:=-DSTM32F205xx

#*****************************************************************************
#Output files
EXECUTABLE=$(PROJ_NAME).elf
BIN_IMAGE=$(PROJ_NAME).bin

#*****************************************************************************
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
OBJSIZE=arm-none-eabi-size


#*****************************************************************************
DEBUG_DIR = ./Debug
RELEASE_DIR = ./Release

		
all:
	make release
	make elf
	make list
	make hex
	make bin
	$(OBJSIZE) $(OBJ_ELF_RELEASE)

all-debug:
	make debug
	make elf-debug
	make list-debug
	make hex-debug
	make bin-debug
	$(OBJSIZE) $(OBJ_ELF_DEBUG)
	
	
#*****************************************************************************
#************************ CMSIS OBJ ******************************************
#*****************************************************************************

#************************ CMSIS OBJ GENERAL **********************************
DIR_SRC_CMSIS:=CMSIS/src
DIR_INC_CMSIS:=CMSIS/inc
DIR_INC_CMSIS_DEV:= CMSIS/Device/ST/STM32F2xx/Include

INC_CMSIS := $(DIR_INC_CMSIS)/
SRC_CMSIS = $(wildcard $(DIR_SRC_CMSIS)/*.c)

#************************ CMSIS OBJ DEBUG ************************************
DIR_CMSIS_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_CMSIS)
OBJ_CMSIS_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_CMSIS)/*.c))

cmsis-debug: $(OBJ_CMSIS_DEBUG)
	
$(DIR_CMSIS_DEBUG)/%.o : $(DIR_SRC_CMSIS)/%.c
	mkdir -p $(DIR_CMSIS_DEBUG)
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o $@

#************************ CMSIS OBJ RELEASE ************************************
DIR_CMSIS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_CMSIS)
OBJ_CMSIS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_CMSIS)/*.c))

cmsis: $(OBJ_CMSIS_RELEASE)
	
$(DIR_CMSIS_RELEASE)/%.o : $(DIR_SRC_CMSIS)/%.c
	mkdir -p $(DIR_CMSIS_RELEASE)
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) $(DEFSYMB) -c -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfloat-abi=soft -mthumb -o $@


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
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) -g3 -DDEBUG $(DEFSYMB)-c -I"$(DIR_INC_LIBS)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections  -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o $@

#************************ LIBS OBJ RELEASE ***********************************
DIR_LIBS_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_LIBS)
OBJ_LIBS_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_LIBS)/*.c))

libs: $(OBJ_LIBS_RELEASE)

$(DIR_LIBS_RELEASE)/%.o : $(DIR_SRC_LIBS)/%.c
	mkdir -p $(DIR_LIBS_RELEASE)
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfloat-abi=soft -mthumb -o $@


#*****************************************************************************
#************************ CORE OBJ *******************************************
#*****************************************************************************

#************************ CORE OBJ GENERAL ***********************************
DIR_SRC_CORE:=Core/src
DIR_INC_CORE:=Core/inc

#Empty dir
INC_LIBS := $(DIR_INC_CORE)/
SRC_LIBS = $(wildcard $(DIR_SRC_CORE)/*.c)

#************************ CORE OBJ DEBUG *************************************
DIR_CORE_DEBUG := $(DEBUG_DIR)/$(DIR_SRC_CORE)
OBJ_CORE_DEBUG := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(wildcard $(DIR_SRC_CORE)/*.c))

core-debug: $(OBJ_CORE_DEBUG)

$(DIR_CORE_DEBUG)/%.o : $(DIR_SRC_CORE)/%.c
	mkdir -p $(DIR_CORE_DEBUG)
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) -g3 -DDEBUG $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o $@

#************************ CORE OBJ RELEASE ***********************************
DIR_CORE_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_CORE)
OBJ_CORE_RELEASE := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(wildcard $(DIR_SRC_CORE)/*.c))

core: $(OBJ_CORE_RELEASE)

$(DIR_CORE_RELEASE)/%.o : $(DIR_SRC_CORE)/%.c
	mkdir -p $(DIR_CORE_RELEASE)
	$(CC) $^ -mcpu=cortex-m3 $(CSTANDART) $(DEFSYMB) -c -I"$(DIR_INC_CORE)" -I "$(DIR_INC_CMSIS)" -I "$(DIR_INC_CMSIS_DEV)" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion --specs=nano.specs -mfloat-abi=soft -mthumb -o $@


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
	$(CC) $^ -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o $(DIR_STARTUP_DEBUG)/$(STARTUP_NAME).o $(DIR_SRC_STARTUP)/$(STARTUP_NAME).s
	
#************************ STARTUP OBJ RELEASE ********************************
DIR_STARTUP_RELEASE := $(RELEASE_DIR)/$(DIR_SRC_STARTUP)
OBJ_STARTUP_RELEASE := $(DIR_STARTUP_RELEASE)/$(STARTUP_NAME).o

startup: $(OBJ_STARTUP_RELEASE)

$(OBJ_STARTUP_RELEASE) : $(STARTUP_SRC)
	mkdir -p $(DIR_STARTUP_RELEASE)	
	$(CC) $^ -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o $(DIR_STARTUP_RELEASE)/$(STARTUP_NAME).o $(DIR_SRC_STARTUP)/$(STARTUP_NAME).s
	

#*****************************************************************************
#************************ ELF OBJ ********************************************
#*****************************************************************************

DIR_SRC_STARTUP:=Startup

STARTUP_SRC:=$(DIR_SRC_STARTUP)/$(STARTUP_NAME).s
OBJ_ELF_DEBUG := $(DEBUG_DIR)/$(EXECUTABLE)

#**************************** ELF DEBUG **************************************
elf-debug: $(OBJ_ELF_DEBUG)

$(OBJ_ELF_DEBUG) : $(STARTUP_SRC) $(DIR_INC_CORE) $(DIR_INC_CMSIS) $(DIR_INC_CMSIS_DEV)
	mkdir -p $(DEBUG_DIR)
	$(CC) -o $(OBJ_ELF_DEBUG) $(OBJ_CORE_DEBUG) $(OBJ_LIBS_DEBUG) $(OBJ_CMSIS_DEBUG) $(OBJ_STARTUP_DEBUG) -mcpu=cortex-m3 -T $(DIR_SRC_STARTUP)/$(LINKER_SCRIPT) --specs=nosys.specs -Wl,-Map=$(DEBUG_DIR)/$(PROJ_NAME).map -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

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

$(OBJ_ELF_RELEASE) : $(STARTUP_SRC) $(DIR_INC_CORE) $(DIR_INC_CMSIS) $(DIR_INC_CMSIS_DEV)
	mkdir -p $(RELEASE_DIR)
	$(CC) -o $(OBJ_ELF_RELEASE) $(OBJ_CORE_RELEASE) $(OBJ_LIBS_RELEASE) $(OBJ_CMSIS_RELEASE) $(OBJ_STARTUP_RELEASE) -mcpu=cortex-m3 -T $(DIR_SRC_STARTUP)/$(LINKER_SCRIPT) --specs=nosys.specs -Wl,-Map=$(RELEASE_DIR)/$(PROJ_NAME).map -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

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

























