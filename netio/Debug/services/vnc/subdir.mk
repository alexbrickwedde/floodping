################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/vnc/vnc.c \
../services/vnc/vnc_block_factory.c 

OBJS += \
./services/vnc/vnc.o \
./services/vnc/vnc_block_factory.o 

C_DEPS += \
./services/vnc/vnc.d \
./services/vnc/vnc_block_factory.d 


# Each subdirectory must supply rules for building sources it contributes
services/vnc/%.o: ../services/vnc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


