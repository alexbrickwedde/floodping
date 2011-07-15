################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/nmea/nmea.c \
../protocols/nmea/nmea_ecmd.c 

OBJS += \
./protocols/nmea/nmea.o \
./protocols/nmea/nmea_ecmd.o 

C_DEPS += \
./protocols/nmea/nmea.d \
./protocols/nmea/nmea_ecmd.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/nmea/%.o: ../protocols/nmea/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


