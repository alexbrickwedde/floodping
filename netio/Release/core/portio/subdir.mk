################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../core/portio/ecmd_simple.o 

C_SRCS += \
../core/portio/ecmd.c \
../core/portio/ecmd_base.c \
../core/portio/ecmd_np.c \
../core/portio/ecmd_simple.c \
../core/portio/named_pin.c \
../core/portio/portio.c \
../core/portio/user_config.c 

OBJS += \
./core/portio/ecmd.o \
./core/portio/ecmd_base.o \
./core/portio/ecmd_np.o \
./core/portio/ecmd_simple.o \
./core/portio/named_pin.o \
./core/portio/portio.o \
./core/portio/user_config.o 

C_DEPS += \
./core/portio/ecmd.d \
./core/portio/ecmd_base.d \
./core/portio/ecmd_np.d \
./core/portio/ecmd_simple.d \
./core/portio/named_pin.d \
./core/portio/portio.d \
./core/portio/user_config.d 


# Each subdirectory must supply rules for building sources it contributes
core/portio/%.o: ../core/portio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


