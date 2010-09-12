################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/modbus/modbus.c \
../protocols/modbus/modbus_client.c \
../protocols/modbus/modbus_client_cb.c \
../protocols/modbus/modbus_ecmd.c \
../protocols/modbus/modbus_net.c 

OBJS += \
./protocols/modbus/modbus.o \
./protocols/modbus/modbus_client.o \
./protocols/modbus/modbus_client_cb.o \
./protocols/modbus/modbus_ecmd.o \
./protocols/modbus/modbus_net.o 

C_DEPS += \
./protocols/modbus/modbus.d \
./protocols/modbus/modbus_client.d \
./protocols/modbus/modbus_client_cb.d \
./protocols/modbus/modbus_ecmd.d \
./protocols/modbus/modbus_net.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/modbus/%.o: ../protocols/modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


