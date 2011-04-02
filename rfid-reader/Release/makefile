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
rfid-reader.lss \

FLASH_IMAGE += \
rfid-reader.hex \

EEPROM_IMAGE += \
rfid-reader.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: rfid-reader.elf secondary-outputs

# Tool invocations
rfid-reader.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,rfid-reader.map -mmcu=attiny2313 -o"rfid-reader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

rfid-reader.lss: rfid-reader.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S rfid-reader.elf  >"rfid-reader.lss"
	@echo 'Finished building: $@'
	@echo ' '

rfid-reader.hex: rfid-reader.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex rfid-reader.elf  "rfid-reader.hex"
	@echo 'Finished building: $@'
	@echo ' '

rfid-reader.eep: rfid-reader.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex rfid-reader.elf  "rfid-reader.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: rfid-reader.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 rfid-reader.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) rfid-reader.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
