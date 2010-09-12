################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/dac/ecmd.c \
../hardware/dac/ltc1257.c \
../hardware/dac/ltc1257_ecmd.c \
../hardware/dac/tlc5620.c 

OBJS += \
./hardware/dac/ecmd.o \
./hardware/dac/ltc1257.o \
./hardware/dac/ltc1257_ecmd.o \
./hardware/dac/tlc5620.o 

C_DEPS += \
./hardware/dac/ecmd.d \
./hardware/dac/ltc1257.d \
./hardware/dac/ltc1257_ecmd.d \
./hardware/dac/tlc5620.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/dac/%.o: ../hardware/dac/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


