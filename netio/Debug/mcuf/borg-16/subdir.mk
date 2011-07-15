################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcuf/borg-16/snake.c \
../mcuf/borg-16/xoni_study.c 

OBJS += \
./mcuf/borg-16/snake.o \
./mcuf/borg-16/xoni_study.o 

C_DEPS += \
./mcuf/borg-16/snake.d \
./mcuf/borg-16/xoni_study.d 


# Each subdirectory must supply rules for building sources it contributes
mcuf/borg-16/%.o: ../mcuf/borg-16/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


