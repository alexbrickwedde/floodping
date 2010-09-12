################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../1wire.c \
../main.c \
../rf12.c \
../tempmeas.c \
../timebase.c 

OBJS += \
./1wire.o \
./main.o \
./rf12.o \
./tempmeas.o \
./timebase.o 

C_DEPS += \
./1wire.d \
./main.d \
./rf12.d \
./tempmeas.d \
./timebase.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny2313 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


