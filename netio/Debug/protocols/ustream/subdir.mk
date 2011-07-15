################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocols/ustream/ustream.c \
../protocols/ustream/ustream_ecmd.c \
../protocols/ustream/vs1053.c 

OBJS += \
./protocols/ustream/ustream.o \
./protocols/ustream/ustream_ecmd.o \
./protocols/ustream/vs1053.o 

C_DEPS += \
./protocols/ustream/ustream.d \
./protocols/ustream/ustream_ecmd.d \
./protocols/ustream/vs1053.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/ustream/%.o: ../protocols/ustream/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


