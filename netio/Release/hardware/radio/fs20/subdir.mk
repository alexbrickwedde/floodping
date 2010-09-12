################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/radio/fs20/fs20.c \
../hardware/radio/fs20/fs20_ecmd.c 

OBJS += \
./hardware/radio/fs20/fs20.o \
./hardware/radio/fs20/fs20_ecmd.o 

C_DEPS += \
./hardware/radio/fs20/fs20.d \
./hardware/radio/fs20/fs20_ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/radio/fs20/%.o: ../hardware/radio/fs20/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


