################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/adc/ads7822/ads7822.c \
../hardware/adc/ads7822/ecmd.c 

OBJS += \
./hardware/adc/ads7822/ads7822.o \
./hardware/adc/ads7822/ecmd.o 

C_DEPS += \
./hardware/adc/ads7822/ads7822.d \
./hardware/adc/ads7822/ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/adc/ads7822/%.o: ../hardware/adc/ads7822/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


