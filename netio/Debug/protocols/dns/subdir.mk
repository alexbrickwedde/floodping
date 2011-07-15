################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../protocols/dns/dns_ecmd.o \
../protocols/dns/dns_net.o \
../protocols/dns/resolv.o 

C_SRCS += \
../protocols/dns/dns_ecmd.c \
../protocols/dns/dns_net.c \
../protocols/dns/resolv.c 

OBJS += \
./protocols/dns/dns_ecmd.o \
./protocols/dns/dns_net.o \
./protocols/dns/resolv.o 

C_DEPS += \
./protocols/dns/dns_ecmd.d \
./protocols/dns/dns_net.d \
./protocols/dns/resolv.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/dns/%.o: ../protocols/dns/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


