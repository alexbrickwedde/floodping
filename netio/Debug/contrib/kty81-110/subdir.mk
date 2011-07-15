################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/kty81-110/kty-calibrate.c \
../contrib/kty81-110/kty-merge.c \
../contrib/kty81-110/nc_udp.c 

OBJS += \
./contrib/kty81-110/kty-calibrate.o \
./contrib/kty81-110/kty-merge.o \
./contrib/kty81-110/nc_udp.o 

C_DEPS += \
./contrib/kty81-110/kty-calibrate.d \
./contrib/kty81-110/kty-merge.d \
./contrib/kty81-110/nc_udp.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/kty81-110/%.o: ../contrib/kty81-110/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


