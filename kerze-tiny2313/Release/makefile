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
kerze.lss \

FLASH_IMAGE += \
kerze.hex \

EEPROM_IMAGE += \
kerze.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: kerze.elf secondary-outputs

# Tool invocations
kerze.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,kerze.map -mmcu=attiny2313 -o"kerze.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

kerze.lss: kerze.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S kerze.elf  >"kerze.lss"
	@echo 'Finished building: $@'
	@echo ' '

kerze.hex: kerze.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex kerze.elf  "kerze.hex"
	@echo 'Finished building: $@'
	@echo ' '

kerze.eep: kerze.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex kerze.elf  "kerze.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: kerze.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 kerze.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) kerze.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
