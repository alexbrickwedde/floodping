################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/ir/rc5/ecmd.c \
../hardware/ir/rc5/rc5.c \
../hardware/ir/rc5/rc5_net.c 

OBJS += \
./hardware/ir/rc5/ecmd.o \
./hardware/ir/rc5/rc5.o \
./hardware/ir/rc5/rc5_net.o 

C_DEPS += \
./hardware/ir/rc5/ecmd.d \
./hardware/ir/rc5/rc5.d \
./hardware/ir/rc5/rc5_net.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/ir/rc5/%.o: ../hardware/ir/rc5/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


