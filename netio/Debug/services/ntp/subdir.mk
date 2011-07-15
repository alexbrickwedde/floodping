################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/ntp/ntp.c \
../services/ntp/ntp_ecmd.c \
../services/ntp/ntpd_net.c 

OBJS += \
./services/ntp/ntp.o \
./services/ntp/ntp_ecmd.o \
./services/ntp/ntpd_net.o 

C_DEPS += \
./services/ntp/ntp.d \
./services/ntp/ntp_ecmd.d \
./services/ntp/ntpd_net.d 


# Each subdirectory must supply rules for building sources it contributes
services/ntp/%.o: ../services/ntp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


