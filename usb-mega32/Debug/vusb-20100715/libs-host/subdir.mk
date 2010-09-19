################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vusb-20100715/libs-host/hiddata.c \
../vusb-20100715/libs-host/opendevice.c 

OBJS += \
./vusb-20100715/libs-host/hiddata.o \
./vusb-20100715/libs-host/opendevice.o 

C_DEPS += \
./vusb-20100715/libs-host/hiddata.d \
./vusb-20100715/libs-host/opendevice.d 


# Each subdirectory must supply rules for building sources it contributes
vusb-20100715/libs-host/%.o: ../vusb-20100715/libs-host/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


