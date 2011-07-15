################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/dmx/dmx.c \
../protocols/dmx/ecmd.c 

OBJS += \
./protocols/dmx/dmx.o \
./protocols/dmx/ecmd.o 

C_DEPS += \
./protocols/dmx/dmx.d \
./protocols/dmx/ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/dmx/%.o: ../protocols/dmx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


