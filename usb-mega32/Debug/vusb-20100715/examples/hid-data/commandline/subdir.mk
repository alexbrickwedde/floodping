################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vusb-20100715/examples/hid-data/commandline/hiddata.c \
../vusb-20100715/examples/hid-data/commandline/hidtool.c 

OBJS += \
./vusb-20100715/examples/hid-data/commandline/hiddata.o \
./vusb-20100715/examples/hid-data/commandline/hidtool.o 

C_DEPS += \
./vusb-20100715/examples/hid-data/commandline/hiddata.d \
./vusb-20100715/examples/hid-data/commandline/hidtool.d 


# Each subdirectory must supply rules for building sources it contributes
vusb-20100715/examples/hid-data/commandline/%.o: ../vusb-20100715/examples/hid-data/commandline/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


