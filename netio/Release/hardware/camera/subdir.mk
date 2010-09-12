################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/camera/dc3840-util.c \
../hardware/camera/dc3840.c \
../hardware/camera/vfs_dc3840.c 

OBJS += \
./hardware/camera/dc3840-util.o \
./hardware/camera/dc3840.o \
./hardware/camera/vfs_dc3840.o 

C_DEPS += \
./hardware/camera/dc3840-util.d \
./hardware/camera/dc3840.d \
./hardware/camera/vfs_dc3840.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/camera/%.o: ../hardware/camera/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


