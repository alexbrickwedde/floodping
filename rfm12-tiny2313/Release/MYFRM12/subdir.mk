################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYFRM12/main.c \
../MYFRM12/myrfm12_example_receiver.c \
../MYFRM12/myrfm12_example_transmitter.c \
../MYFRM12/uart.c 

OBJS += \
./MYFRM12/main.o \
./MYFRM12/myrfm12_example_receiver.o \
./MYFRM12/myrfm12_example_transmitter.o \
./MYFRM12/uart.o 

C_DEPS += \
./MYFRM12/main.d \
./MYFRM12/myrfm12_example_receiver.d \
./MYFRM12/myrfm12_example_transmitter.d \
./MYFRM12/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MYFRM12/%.o: ../MYFRM12/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny2313 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


