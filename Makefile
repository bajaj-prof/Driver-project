TARGET_HW=launchpad
TARGET_NAME=$(TARGET_HW)


#Directories
TOOLS_DIR = ${TOOLS_PATH}
MSPGCC_ROOT_DIR = $(TOOLS_DIR)/msp430-gcc-9.3.1.11_linux64
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUDE_DIRS = $(MSPGCC_INCLUDE_DIR)\
				./src \
				./external/ \
				./
				
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)
BUILD_DIR = builds
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
TI_CCS_DIR = /home/vishalb/ti/ccs1260/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

#Toolchains
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM = rm
DEBUG = LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug
CPPCHECK = cppcheck
FORMAT = clang-format-12
READELF = $(MSPGCC_BIN_DIR) /msp430-elf-readelf
ADDR2LINE = $(MSPGCC_BIN_DIR)/msp430-elf-addr2line

#Files
TARGET = $(BIN_DIR)/test

MAIN_FILE = src/test/test.c

SOURCES_WITH_HEADERS =	\
	src/drivers/mcu_init.c \
	src/drivers/io.c \
	src/drivers/uart.c \
	src/common/ring_buffer.c \
	external/printf/printf.c \
	src/common/trace.c \
	src/common/assert_handler.c 

       				  

SOURCES = $(SOURCES_WITH_HEADERS) \
         $(MAIN_FILE)
         
HEADERS = $(SOURCES_WITH_HEADERS:.c=.h) \
          src/common/defines.h \        

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES)) 

#Defines
DEFINES = \
	-DPRINTF_INCLUDE_CONFIG_H \
#Static Analysis 
#Don't check the msp430 helper headers (have a lot of ifdefs)
CPPCHECK_INCLUDES = ./src ./
IGNORE_FILES_FORMAT_CPPCHECK = \
		external/printf/printf.h \
		external/printf/printf.c \

SOURCES_FORMAT_CPPCHECK = $(filter-out $(IGNORE_FILES_FORMAT_CPPCHECK),$(SOURCES))

HEADER_FORMAT = $(filter-out $(IGNORE_FILES_FORMAT_CPPCHECK),$(HEADERS))

#Flags
MCU = msp430g2553
WFLAGS = -Wall -Wextra  -Werror -Wshadow 
CFLAGS = -mmcu=$(MCU)  $(WFLAGS) $(addprefix -I,$(INCLUDE_DIRS)) $(DEFINES) -Og -g 
LDFLAGS = -mmcu=$(MCU) $(addprefix -L,$(LIB_DIRS))
CPPCHECK_FLAGS = \
	--quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	$(addprefix -I,$(CPPCHECK_INCLUDES)) \

#Build

#Linking
$(TARGET): $(OBJECTS) 
	@echo "Linking $^"
	@mkdir -p $(dir  $@) 
	$(CC) $(LDFLAGS) -o $@ $^

#Compiling
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^


#PHONIES

.PHONY: all clean flash cppcheck format headers objects target

all: $(TARGET) 

clean:
	$(RM) -rf $(BUILD_DIR)
	
flash: $(TARGET)
	$(DEBUG) rf2500 "erase" "load $(TARGET)"

cppcheck:
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES_FORMAT_CPPCHECK)	
	
format:
	$(FORMAT) -i $(SOURCES_FORMAT_CPPCHECK) $(HEADERS_FORMAT)			

headers: 
	@echo $(HEADERS)
	
objects:
	@echo $(OBJECTS)	

target: 
	@echo $(TARGET)
	
addr2line : $(TARGET)
	@ $(ADDR2LINE) -e $(TARGET) $(ADDR)