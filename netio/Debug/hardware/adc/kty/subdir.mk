################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/adc/kty/ecmd.c \
../hardware/adc/kty/kty81.c 

OBJS += \
./hardware/adc/kty/ecmd.o \
./hardware/adc/kty/kty81.o 

C_DEPS += \
./hardware/adc/kty/ecmd.d \
./hardware/adc/kty/kty81.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/adc/kty/%.o: ../hardware/adc/kty/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


