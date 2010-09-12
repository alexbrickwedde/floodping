################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../protocols/ecmd/parser.o 

C_SRCS += \
../protocols/ecmd/aliascmd.c \
../protocols/ecmd/parser.c \
../protocols/ecmd/scripting.c 

OBJS += \
./protocols/ecmd/aliascmd.o \
./protocols/ecmd/parser.o \
./protocols/ecmd/scripting.o 

C_DEPS += \
./protocols/ecmd/aliascmd.d \
./protocols/ecmd/parser.d \
./protocols/ecmd/scripting.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/ecmd/%.o: ../protocols/ecmd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


