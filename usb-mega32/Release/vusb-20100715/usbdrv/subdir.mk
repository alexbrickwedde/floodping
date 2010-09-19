################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vusb-20100715/usbdrv/oddebug.c \
../vusb-20100715/usbdrv/usbdrv.c 

S_UPPER_SRCS += \
../vusb-20100715/usbdrv/usbdrvasm.S 

ASM_SRCS += \
../vusb-20100715/usbdrv/usbdrvasm.asm 

OBJS += \
./vusb-20100715/usbdrv/oddebug.o \
./vusb-20100715/usbdrv/usbdrv.o \
./vusb-20100715/usbdrv/usbdrvasm.o 

C_DEPS += \
./vusb-20100715/usbdrv/oddebug.d \
./vusb-20100715/usbdrv/usbdrv.d 

ASM_DEPS += \
./vusb-20100715/usbdrv/usbdrvasm.d 

S_UPPER_DEPS += \
./vusb-20100715/usbdrv/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
vusb-20100715/usbdrv/%.o: ../vusb-20100715/usbdrv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vusb-20100715/usbdrv/%.o: ../vusb-20100715/usbdrv/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vusb-20100715/usbdrv/%.o: ../vusb-20100715/usbdrv/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


