################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/ultrasonic/ecmd.c \
../hardware/ultrasonic/srf05.c 

OBJS += \
./hardware/ultrasonic/ecmd.o \
./hardware/ultrasonic/srf05.o 

C_DEPS += \
./hardware/ultrasonic/ecmd.d \
./hardware/ultrasonic/srf05.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/ultrasonic/%.o: ../hardware/ultrasonic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


