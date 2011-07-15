################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/storage/dataflash/df.c \
../hardware/storage/dataflash/ecmd.c \
../hardware/storage/dataflash/fs.c \
../hardware/storage/dataflash/vfs_df.c 

OBJS += \
./hardware/storage/dataflash/df.o \
./hardware/storage/dataflash/ecmd.o \
./hardware/storage/dataflash/fs.o \
./hardware/storage/dataflash/vfs_df.o 

C_DEPS += \
./hardware/storage/dataflash/df.d \
./hardware/storage/dataflash/ecmd.d \
./hardware/storage/dataflash/fs.d \
./hardware/storage/dataflash/vfs_df.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/storage/dataflash/%.o: ../hardware/storage/dataflash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


