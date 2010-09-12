################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/serial_line_log/serial_line_log.c \
../protocols/serial_line_log/serial_line_log_ecmd.c 

OBJS += \
./protocols/serial_line_log/serial_line_log.o \
./protocols/serial_line_log/serial_line_log_ecmd.o 

C_DEPS += \
./protocols/serial_line_log/serial_line_log.d \
./protocols/serial_line_log/serial_line_log_ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/serial_line_log/%.o: ../protocols/serial_line_log/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


