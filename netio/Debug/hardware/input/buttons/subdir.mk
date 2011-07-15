################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/input/buttons/buttons.c \
../hardware/input/buttons/ecmd.c \
../hardware/input/buttons/joystick_digital.c 

OBJS += \
./hardware/input/buttons/buttons.o \
./hardware/input/buttons/ecmd.o \
./hardware/input/buttons/joystick_digital.o 

C_DEPS += \
./hardware/input/buttons/buttons.d \
./hardware/input/buttons/ecmd.d \
./hardware/input/buttons/joystick_digital.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/input/buttons/%.o: ../hardware/input/buttons/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


