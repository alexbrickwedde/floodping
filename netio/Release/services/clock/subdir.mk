################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/clock/clock.c \
../services/clock/clock_ecmd_date.c \
../services/clock/clock_ecmd_time.c \
../services/clock/clock_soap.c \
../services/clock/whm_ecmd.c \
../services/clock/whm_soap.c 

OBJS += \
./services/clock/clock.o \
./services/clock/clock_ecmd_date.o \
./services/clock/clock_ecmd_time.o \
./services/clock/clock_soap.o \
./services/clock/whm_ecmd.o \
./services/clock/whm_soap.o 

C_DEPS += \
./services/clock/clock.d \
./services/clock/clock_ecmd_date.d \
./services/clock/clock_ecmd_time.d \
./services/clock/clock_soap.d \
./services/clock/whm_ecmd.d \
./services/clock/whm_soap.d 


# Each subdirectory must supply rules for building sources it contributes
services/clock/%.o: ../services/clock/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


