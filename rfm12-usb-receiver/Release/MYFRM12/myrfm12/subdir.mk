################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYFRM12/myrfm12/myrfm12.c \
../MYFRM12/myrfm12/myrfm12conf.c 

OBJS += \
./MYFRM12/myrfm12/myrfm12.o \
./MYFRM12/myrfm12/myrfm12conf.o 

C_DEPS += \
./MYFRM12/myrfm12/myrfm12.d \
./MYFRM12/myrfm12/myrfm12conf.d 


# Each subdirectory must supply rules for building sources it contributes
MYFRM12/myrfm12/%.o: ../MYFRM12/myrfm12/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny2313 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


