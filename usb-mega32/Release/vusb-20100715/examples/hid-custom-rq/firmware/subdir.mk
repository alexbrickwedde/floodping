################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vusb-20100715/examples/hid-custom-rq/firmware/main.c 

OBJS += \
./vusb-20100715/examples/hid-custom-rq/firmware/main.o 

C_DEPS += \
./vusb-20100715/examples/hid-custom-rq/firmware/main.d 


# Each subdirectory must supply rules for building sources it contributes
vusb-20100715/examples/hid-custom-rq/firmware/%.o: ../vusb-20100715/examples/hid-custom-rq/firmware/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


