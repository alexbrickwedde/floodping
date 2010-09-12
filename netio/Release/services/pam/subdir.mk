################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/pam/pam_ldap.c \
../services/pam/pam_none.c \
../services/pam/pam_single_user.c \
../services/pam/pam_single_user_eeprom.c 

OBJS += \
./services/pam/pam_ldap.o \
./services/pam/pam_none.o \
./services/pam/pam_single_user.o \
./services/pam/pam_single_user_eeprom.o 

C_DEPS += \
./services/pam/pam_ldap.d \
./services/pam/pam_none.d \
./services/pam/pam_single_user.d \
./services/pam/pam_single_user_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
services/pam/%.o: ../services/pam/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


