################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/tftp/tftp-bootload.c \
../services/tftp/tftp-vfs.c \
../services/tftp/tftp_net.c 

OBJS += \
./services/tftp/tftp-bootload.o \
./services/tftp/tftp-vfs.o \
./services/tftp/tftp_net.o 

C_DEPS += \
./services/tftp/tftp-bootload.d \
./services/tftp/tftp-vfs.d \
./services/tftp/tftp_net.d 


# Each subdirectory must supply rules for building sources it contributes
services/tftp/%.o: ../services/tftp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


