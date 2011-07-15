################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/jabber/jabber.c \
../services/jabber/jabber_ecmd.c 

OBJS += \
./services/jabber/jabber.o \
./services/jabber/jabber_ecmd.o 

C_DEPS += \
./services/jabber/jabber.d \
./services/jabber/jabber_ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
services/jabber/%.o: ../services/jabber/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


