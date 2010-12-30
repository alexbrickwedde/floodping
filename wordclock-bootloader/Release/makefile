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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
wordclock-bootloader.lss \

FLASH_IMAGE += \
wordclock-bootloader.hex \

EEPROM_IMAGE += \
wordclock-bootloader.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: wordclock-bootloader.elf secondary-outputs

# Tool invocations
wordclock-bootloader.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,wordclock-bootloader.map -Ttext=0x7000 -mmcu=atmega32 -o"wordclock-bootloader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

wordclock-bootloader.lss: wordclock-bootloader.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S wordclock-bootloader.elf  >"wordclock-bootloader.lss"
	@echo 'Finished building: $@'
	@echo ' '

wordclock-bootloader.hex: wordclock-bootloader.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex wordclock-bootloader.elf  "wordclock-bootloader.hex"
	@echo 'Finished building: $@'
	@echo ' '

wordclock-bootloader.eep: wordclock-bootloader.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex wordclock-bootloader.elf  "wordclock-bootloader.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: wordclock-bootloader.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 wordclock-bootloader.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) wordclock-bootloader.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
