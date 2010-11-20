################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

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
libvusb.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libvusb.a secondary-outputs

# Tool invocations
libvusb.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r "libvusb.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libvusb.lss: libvusb.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libvusb.a  >"libvusb.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libvusb.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 libvusb.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ARCHIVES)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) libvusb.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
