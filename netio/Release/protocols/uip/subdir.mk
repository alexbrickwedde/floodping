################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../protocols/uip/check_cache.o \
../protocols/uip/ecmd.o \
../protocols/uip/parse.o \
../protocols/uip/uip.o \
../protocols/uip/uip_arp.o \
../protocols/uip/uip_multi.o \
../protocols/uip/uip_rfm12.o \
../protocols/uip/uip_router.o 

C_SRCS += \
../protocols/uip/check_cache.c \
../protocols/uip/ecmd.c \
../protocols/uip/ipstats.c \
../protocols/uip/ipv6.c \
../protocols/uip/parse.c \
../protocols/uip/uip.c \
../protocols/uip/uip_arp.c \
../protocols/uip/uip_multi.c \
../protocols/uip/uip_neighbor.c \
../protocols/uip/uip_openvpn.c \
../protocols/uip/uip_rfm12.c \
../protocols/uip/uip_router.c \
../protocols/uip/uip_zbus.c 

OBJS += \
./protocols/uip/check_cache.o \
./protocols/uip/ecmd.o \
./protocols/uip/ipstats.o \
./protocols/uip/ipv6.o \
./protocols/uip/parse.o \
./protocols/uip/uip.o \
./protocols/uip/uip_arp.o \
./protocols/uip/uip_multi.o \
./protocols/uip/uip_neighbor.o \
./protocols/uip/uip_openvpn.o \
./protocols/uip/uip_rfm12.o \
./protocols/uip/uip_router.o \
./protocols/uip/uip_zbus.o 

C_DEPS += \
./protocols/uip/check_cache.d \
./protocols/uip/ecmd.d \
./protocols/uip/ipstats.d \
./protocols/uip/ipv6.d \
./protocols/uip/parse.d \
./protocols/uip/uip.d \
./protocols/uip/uip_arp.d \
./protocols/uip/uip_multi.d \
./protocols/uip/uip_neighbor.d \
./protocols/uip/uip_openvpn.d \
./protocols/uip/uip_rfm12.d \
./protocols/uip/uip_router.d \
./protocols/uip/uip_zbus.d 


# Each subdirectory must supply rules for building sources it contributes
protocols/uip/%.o: ../protocols/uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


