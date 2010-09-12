################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/lcd/s1d13305/s1d13305.c 

OBJS += \
./hardware/lcd/s1d13305/s1d13305.o 

C_DEPS += \
./hardware/lcd/s1d13305/s1d13305.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/lcd/s1d13305/%.o: ../hardware/lcd/s1d13305/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


