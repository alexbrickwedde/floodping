################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../hardware/avr/bootloader_ecmd.o \
../hardware/avr/dump_ecmd.o \
../hardware/avr/fuse.o \
../hardware/avr/hostname.o \
../hardware/avr/reset_ecmd.o 

C_SRCS += \
../hardware/avr/bootloader_ecmd.c \
../hardware/avr/dump_ecmd.c \
../hardware/avr/eeprom_ecmd.c \
../hardware/avr/fuse.c \
../hardware/avr/hostname.c \
../hardware/avr/reset_ecmd.c 

OBJS += \
./hardware/avr/bootloader_ecmd.o \
./hardware/avr/dump_ecmd.o \
./hardware/avr/eeprom_ecmd.o \
./hardware/avr/fuse.o \
./hardware/avr/hostname.o \
./hardware/avr/reset_ecmd.o 

C_DEPS += \
./hardware/avr/bootloader_ecmd.d \
./hardware/avr/dump_ecmd.d \
./hardware/avr/eeprom_ecmd.d \
./hardware/avr/fuse.d \
./hardware/avr/hostname.d \
./hardware/avr/reset_ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/avr/%.o: ../hardware/avr/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


