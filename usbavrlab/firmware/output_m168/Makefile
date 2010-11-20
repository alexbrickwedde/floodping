###############################################################################
# Makefile for the project AVRISP
###############################################################################

## General Flags
PROJECT = AVRISP
MCU = atmega32
TARGET = m168_ATK500+AVR910_1.2.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2     -DHAS_STK500_PROTOCOL                                  -DF_CPU=12000000UL -Os -fsigned-char -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"C:\Users\SonAle\workspace\floodping\usbavrlab\firmware\usbdrv" -I"C:\Users\SonAle\workspace\floodping\usbavrlab\firmware\." 

## Objects that must be built in order to link
OBJECTS = main.o usbdrv.o usbdrvasm.o usb_uart.o isp.o stk500protocol.o timer.o vt100.o vt100_menue.o led.o buffer.o avr910protocol.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) m168_ATK500+AVR910_1.2.hex m168_ATK500+AVR910_1.2.eep m168_ATK500+AVR910_1.2.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usbdrv.o: ../usbdrv/usbdrv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usbdrvasm.o: ../usbdrv/usbdrvasm.S
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

usb_uart.o: ../usb_uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

isp.o: ../isp.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

stk500protocol.o: ../stk500protocol.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

vt100.o: ../vt100.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

vt100_menue.o: ../vt100_menue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led.o: ../led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

buffer.o: ../buffer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

avr910protocol.o: ../avr910protocol.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) m168_ATK500+AVR910_1.2.elf dep/* m168_ATK500+AVR910_1.2.hex m168_ATK500+AVR910_1.2.eep m168_ATK500+AVR910_1.2.lss

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

