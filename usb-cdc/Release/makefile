################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
usb-cdc.lss \

FLASH_IMAGE += \
usb-cdc.hex \

EEPROM_IMAGE += \
usb-cdc.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: usb-cdc.elf secondary-outputs

# Tool invocations
usb-cdc.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,usb-cdc.map,--cref -mmcu=atmega8 -o "usb-cdc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

usb-cdc.lss: usb-cdc.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S usb-cdc.elf  >"usb-cdc.lss"
	@echo 'Finished building: $@'
	@echo ' '

usb-cdc.hex: usb-cdc.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex usb-cdc.elf  "usb-cdc.hex"
	@echo 'Finished building: $@'
	@echo ' '

usb-cdc.eep: usb-cdc.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex usb-cdc.elf  "usb-cdc.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: usb-cdc.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 usb-cdc.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: usb-cdc.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm8 -cusbasp -u -Uflash:w:usb-cdc.hex:a -Ulfuse:w:0xcf:m -Uhfuse:w:0xd9:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(AVRDUDEDUMMY)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) usb-cdc.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
