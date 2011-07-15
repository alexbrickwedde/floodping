################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/i2c/master/ecmd.c \
../hardware/i2c/master/i2c_24CXX.c \
../hardware/i2c/master/i2c_ds1337.c \
../hardware/i2c/master/i2c_ds1631.c \
../hardware/i2c/master/i2c_generic.c \
../hardware/i2c/master/i2c_lm75.c \
../hardware/i2c/master/i2c_master.c \
../hardware/i2c/master/i2c_max7311.c \
../hardware/i2c/master/i2c_pca9531.c \
../hardware/i2c/master/i2c_pcf8574x.c \
../hardware/i2c/master/i2c_tsl2550.c \
../hardware/i2c/master/i2c_udp.c \
../hardware/i2c/master/i2c_udp_net.c \
../hardware/i2c/master/vfs_eeprom.c \
../hardware/i2c/master/vfs_eeprom_raw.c 

OBJS += \
./hardware/i2c/master/ecmd.o \
./hardware/i2c/master/i2c_24CXX.o \
./hardware/i2c/master/i2c_ds1337.o \
./hardware/i2c/master/i2c_ds1631.o \
./hardware/i2c/master/i2c_generic.o \
./hardware/i2c/master/i2c_lm75.o \
./hardware/i2c/master/i2c_master.o \
./hardware/i2c/master/i2c_max7311.o \
./hardware/i2c/master/i2c_pca9531.o \
./hardware/i2c/master/i2c_pcf8574x.o \
./hardware/i2c/master/i2c_tsl2550.o \
./hardware/i2c/master/i2c_udp.o \
./hardware/i2c/master/i2c_udp_net.o \
./hardware/i2c/master/vfs_eeprom.o \
./hardware/i2c/master/vfs_eeprom_raw.o 

C_DEPS += \
./hardware/i2c/master/ecmd.d \
./hardware/i2c/master/i2c_24CXX.d \
./hardware/i2c/master/i2c_ds1337.d \
./hardware/i2c/master/i2c_ds1631.d \
./hardware/i2c/master/i2c_generic.d \
./hardware/i2c/master/i2c_lm75.d \
./hardware/i2c/master/i2c_master.d \
./hardware/i2c/master/i2c_max7311.d \
./hardware/i2c/master/i2c_pca9531.d \
./hardware/i2c/master/i2c_pcf8574x.d \
./hardware/i2c/master/i2c_tsl2550.d \
./hardware/i2c/master/i2c_udp.d \
./hardware/i2c/master/i2c_udp_net.d \
./hardware/i2c/master/vfs_eeprom.d \
./hardware/i2c/master/vfs_eeprom_raw.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/i2c/master/%.o: ../hardware/i2c/master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


