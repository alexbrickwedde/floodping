################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/onewire/ds2450.c \
../hardware/onewire/ds2450_ecmd.c \
../hardware/onewire/ecmd.c \
../hardware/onewire/onewire.c 

OBJS += \
./hardware/onewire/ds2450.o \
./hardware/onewire/ds2450_ecmd.o \
./hardware/onewire/ecmd.o \
./hardware/onewire/onewire.o 

C_DEPS += \
./hardware/onewire/ds2450.d \
./hardware/onewire/ds2450_ecmd.d \
./hardware/onewire/ecmd.d \
./hardware/onewire/onewire.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/onewire/%.o: ../hardware/onewire/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


