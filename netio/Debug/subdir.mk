################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../ethersex.o \
../meta.o \
../network.o 

C_SRCS += \
../ethersex.c \
../meta.c \
../network.c \
../pinning.c 

OBJS += \
./ethersex.o \
./meta.o \
./network.o \
./pinning.o 

C_DEPS += \
./ethersex.d \
./meta.d \
./network.d \
./pinning.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


