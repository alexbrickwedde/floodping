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
klinke.lss \

FLASH_IMAGE += \
klinke.hex \

EEPROM_IMAGE += \
klinke.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: klinke.elf secondary-outputs

# Tool invocations
klinke.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,klinke.map -mmcu=attiny2313 -o"klinke.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

klinke.lss: klinke.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S klinke.elf  >"klinke.lss"
	@echo 'Finished building: $@'
	@echo ' '

klinke.hex: klinke.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex klinke.elf  "klinke.hex"
	@echo 'Finished building: $@'
	@echo ' '

klinke.eep: klinke.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex klinke.elf  "klinke.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: klinke.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 klinke.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) klinke.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
