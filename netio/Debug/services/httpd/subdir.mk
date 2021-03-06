################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/httpd/base64_mit.c \
../services/httpd/handle_400.c \
../services/httpd/handle_401.c \
../services/httpd/handle_404.c \
../services/httpd/handle_ecmd.c \
../services/httpd/handle_sd_dir.c \
../services/httpd/handle_soap.c \
../services/httpd/handle_vfs.c \
../services/httpd/headers.c \
../services/httpd/httpd.c 

OBJS += \
./services/httpd/base64_mit.o \
./services/httpd/handle_400.o \
./services/httpd/handle_401.o \
./services/httpd/handle_404.o \
./services/httpd/handle_ecmd.o \
./services/httpd/handle_sd_dir.o \
./services/httpd/handle_soap.o \
./services/httpd/handle_vfs.o \
./services/httpd/headers.o \
./services/httpd/httpd.o 

C_DEPS += \
./services/httpd/base64_mit.d \
./services/httpd/handle_400.d \
./services/httpd/handle_401.d \
./services/httpd/handle_404.d \
./services/httpd/handle_ecmd.d \
./services/httpd/handle_sd_dir.d \
./services/httpd/handle_soap.d \
./services/httpd/handle_vfs.d \
./services/httpd/headers.d \
./services/httpd/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
services/httpd/%.o: ../services/httpd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


