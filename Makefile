
#Directories
MSPGCC_ROOT_DIR = /home/vishalb/Dev/msp430-gcc-9.3.1.11_linux64
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUDE_DIRS = $(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
TI_CCS_DIR = /home/vishalb/ti/ccs1260/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

#Toolchains
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM = rm
DEBUG = LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug


#Files
TARGET = $(BIN_DIR)/blink

SOURCES = blink.c \
	  led.c

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES)) 

#Flags
MCU = msp430g2553
WFLAGS = -Wall -Wextra  -Werror -Wshadow 
CFLAGS = -mmcu=$(MCU)  $(WFLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -Og -g
LDFLAGS = -mmcu=$(MCU) $(addprefix -L,$(LIB_DIRS)) 

#Build

#Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir  $@) 
	$(CC) $(LDFLAGS) -o $@ $^

#Compiling
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^


#PHONIES

.PHONY: all clean flash

all: $(TARGET) 

clean:
	$(RM) -r $(BUILD_DIR)
flash: $(TARGET)
	$(DEBUG) rf2500 "erase" "load $(TARGET)"

 
