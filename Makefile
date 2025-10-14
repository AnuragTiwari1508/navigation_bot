# Navigation Bot Makefile
# Target: ATmega32
# Programmer: USBasp

# MCU settings
MCU = atmega32
F_CPU = 16000000UL
FORMAT = ihex
TARGET = navigation_bot

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler settings
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size

# Compiler flags
CFLAGS = -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)
CFLAGS += -Os
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -I$(INCDIR)
CFLAGS += -std=gnu99

# Linker flags
LDFLAGS = -mmcu=$(MCU)
LDFLAGS += -Wl,-Map=$(TARGET).map

# Programmer settings
PROGRAMMER = usbasp
AVRDUDE = avrdude
AVRDUDE_FLAGS = -p $(MCU) -c $(PROGRAMMER)

# Default target
all: $(TARGET).hex

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Create hex file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

# Create EEPROM hex file
$(TARGET)_eeprom.hex: $(TARGET).elf
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Display size information
size: $(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

# Program the device
flash: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<:i

# Program EEPROM
eeprom: $(TARGET)_eeprom.hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U eeprom:w:$<:i

# Set fuses for ATmega32 with 16MHz external crystal
fuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xFF:m -U hfuse:w:0xC9:m

# Clean build files
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET)_eeprom.hex $(TARGET).map

# Phony targets
.PHONY: all size flash eeprom fuses clean