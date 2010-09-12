################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/stella/stella.c \
../services/stella/stella_ecmd.c \
../services/stella/stella_pwm.c 

OBJS += \
./services/stella/stella.o \
./services/stella/stella_ecmd.o \
./services/stella/stella_pwm.o 

C_DEPS += \
./services/stella/stella.d \
./services/stella/stella_ecmd.d \
./services/stella/stella_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
services/stella/%.o: ../services/stella/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


