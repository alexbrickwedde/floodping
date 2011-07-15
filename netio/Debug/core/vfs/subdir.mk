################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../core/vfs/vfs-concat.c \
../core/vfs/vfs-util.c \
../core/vfs/vfs.c \
../core/vfs/vfs_inline.c 

OBJS += \
./core/vfs/vfs-concat.o \
./core/vfs/vfs-util.o \
./core/vfs/vfs.o \
./core/vfs/vfs_inline.o 

C_DEPS += \
./core/vfs/vfs-concat.d \
./core/vfs/vfs-util.d \
./core/vfs/vfs.d \
./core/vfs/vfs_inline.d 


# Each subdirectory must supply rules for building sources it contributes
core/vfs/%.o: ../core/vfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


