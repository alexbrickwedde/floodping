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
distancesensor-tiny85.lss \

FLASH_IMAGE += \
distancesensor-tiny85.hex \

EEPROM_IMAGE += \
distancesensor-tiny85.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: distancesensor-tiny85.elf secondary-outputs

# Tool invocations
distancesensor-tiny85.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,distancesensor-tiny85.map,--cref -mmcu=attiny85 -o "distancesensor-tiny85.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

distancesensor-tiny85.lss: distancesensor-tiny85.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S distancesensor-tiny85.elf  >"distancesensor-tiny85.lss"
	@echo 'Finished building: $@'
	@echo ' '

distancesensor-tiny85.hex: distancesensor-tiny85.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex distancesensor-tiny85.elf  "distancesensor-tiny85.hex"
	@echo 'Finished building: $@'
	@echo ' '

distancesensor-tiny85.eep: distancesensor-tiny85.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex distancesensor-tiny85.elf  "distancesensor-tiny85.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: distancesensor-tiny85.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 distancesensor-tiny85.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) distancesensor-tiny85.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
