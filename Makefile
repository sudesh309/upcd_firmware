# Project name
NAME		= firmware

# Location of vendor directory
VEN_DIR		= ti

# Location of source files
C_SRC		+= $(wildcard *.c)
C_SRC		+= $(VEN_DIR)/startup.c

# Directory where the elf/bin gets stored.
BUILD_DIR	= build

# Compiler tools prefix
PREFIX		= arm-none-eabi

# Path of the used linkerscript
LDSCRIPT	= $(VEN_DIR)/linker_script.ld

# Processer variant
CPU		= cortex-m4
FPU		= fpv4-sp-d16 -mfloat-abi=softfp
PART 		= TM4C123

# Files
BIN		= $(BUILD_DIR)/$(NAME).bin
ELF		= $(BUILD_DIR)/$(NAME).elf
MAP		= $(BUILD_DIR)/$(NAME).map

# Tools
CC		= $(PREFIX)-gcc
LD  		= $(PREFIX)-ld
OBJCPY		= $(PREFIX)-objcopy
SIZE		= $(PREFIX)-size
GDB		= $(PREFIX)-gdb
FLASH		= lm4flash
RM		= rm -rf
MKDIR		= mkdir -p

# Debugger stuff
DEBUG_SCRIPT	= debug/start_debugger.sh
GDB_INIT	= debug/gdb_init.gdb

# Paths
vpath	%.c	$(VEN_DIR)/utils/ 

# Flags
INCLUDES	= -I$(VEN_DIR)
DEBUGFLAGS	= -g #-D DEBUG

AFLAGS		+= -mthumb
AFLAGS		+= -mcpu=$(CPU)
AFLAGS		+= -mfpu=$(FPU)
AFLAGS		+= -MD

# C FLAGS
CFLAGS		+= -mthumb 
CFLAGS		+= -mcpu=$(CPU) 
CFLAGS		+= -mfpu=$(FPU) 
CFLAGS		+= -mfloat-abi=softfp 
CFLAGS		+= -Os 
CFLAGS		+= -ffunction-sections 
CFLAGS		+= -fdata-sections 
CFLAGS		+= -MD 
CFLAGS		+= -std=c99 
CFLAGS		+= -Wall 
CFLAGS		+= -pedantic 
CFLAGS		+= -DPART_$(PART)
CFLAGS		+= -DTARGET_IS_BLIZZARD_RA1
CFLAGS		+= $(INCLUDES)

# Linker flags
LDFLAGS		+= -T $(LDSCRIPT) 
LDFLAGS		+= --entry ResetISR 
LDFLAGS		+= --gc-sections
LDFLAGS		+= -nostdlib
LDFLAGS		+= -Map $(MAP)

# Object files
OBJS		=  $(C_SRC:.c=.o)  
OBJS		+= $(ASM_SRC:.S=.o)
C_DEPS		=  $(wildcard *.d)
C_DEPS		+= $(VEN_DIR)/startup.d

# Library locations
LIBS		+= $(VEN_DIR)/usblib/gcc/libusb.a
LIBS		+= $(VEN_DIR)/driverlib/gcc/libdriver.a
LIBS		+= $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)
LIBS		+= $(shell $(CC) $(CFLAGS) -print-file-name=libc.a)
LIBS		+= $(shell $(CC) $(CFLAGS) -print-file-name=libm.a)

.PHONY: stellaris tivac all clean release

all: dir bin size

bin: elf
	$(OBJCPY) -O binary $(ELF) $(BIN) 

elf: $(OBJS) dir
	$(LD) -o $(ELF) $(LDFLAGS) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(C_DEPS) $(BUILD_DIR) 

debug: CFLAGS += $(DEBUGFLAGS)
debug: clean elf
	@sh -c "$(DEBUG_SCRIPT) $(GDB) $(GDB_INIT) $(ELF)"

dir:
	$(MKDIR) $(BUILD_DIR)

flash: bin
	$(FLASH) $(BIN)

size: bin
	$(SIZE) $(ELF)

# Compile 
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(AFLAGS) -c $< -o $@

-include $(C_DEPS)
