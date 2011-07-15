################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../core/tty/tty-vt100-telnet.c \
../core/tty/tty-vt100.c \
../core/tty/tty.c 

OBJS += \
./core/tty/tty-vt100-telnet.o \
./core/tty/tty-vt100.o \
./core/tty/tty.o 

C_DEPS += \
./core/tty/tty-vt100-telnet.d \
./core/tty/tty-vt100.d \
./core/tty/tty.d 


# Each subdirectory must supply rules for building sources it contributes
core/tty/%.o: ../core/tty/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


