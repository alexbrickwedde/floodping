################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/libecmd/rfm12ask_2272/rfm12ask_2272.c 

OBJS += \
./contrib/libecmd/rfm12ask_2272/rfm12ask_2272.o 

C_DEPS += \
./contrib/libecmd/rfm12ask_2272/rfm12ask_2272.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/libecmd/rfm12ask_2272/%.o: ../contrib/libecmd/rfm12ask_2272/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


