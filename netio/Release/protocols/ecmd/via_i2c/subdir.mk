################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/ecmd/via_i2c/ecmd_i2c.c 

OBJS += \
./protocols/ecmd/via_i2c/ecmd_i2c.o 

C_DEPS += \
./protocols/ecmd/via_i2c/ecmd_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/ecmd/via_i2c/%.o: ../protocols/ecmd/via_i2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


