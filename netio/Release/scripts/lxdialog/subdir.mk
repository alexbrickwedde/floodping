################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../scripts/lxdialog/checklist.o \
../scripts/lxdialog/inputbox.o \
../scripts/lxdialog/lxdialog.o \
../scripts/lxdialog/menubox.o \
../scripts/lxdialog/msgbox.o \
../scripts/lxdialog/textbox.o \
../scripts/lxdialog/util.o \
../scripts/lxdialog/yesno.o 

C_SRCS += \
../scripts/lxdialog/checklist.c \
../scripts/lxdialog/inputbox.c \
../scripts/lxdialog/lxdialog.c \
../scripts/lxdialog/menubox.c \
../scripts/lxdialog/msgbox.c \
../scripts/lxdialog/textbox.c \
../scripts/lxdialog/util.c \
../scripts/lxdialog/yesno.c 

OBJS += \
./scripts/lxdialog/checklist.o \
./scripts/lxdialog/inputbox.o \
./scripts/lxdialog/lxdialog.o \
./scripts/lxdialog/menubox.o \
./scripts/lxdialog/msgbox.o \
./scripts/lxdialog/textbox.o \
./scripts/lxdialog/util.o \
./scripts/lxdialog/yesno.o 

C_DEPS += \
./scripts/lxdialog/checklist.d \
./scripts/lxdialog/inputbox.d \
./scripts/lxdialog/lxdialog.d \
./scripts/lxdialog/menubox.d \
./scripts/lxdialog/msgbox.d \
./scripts/lxdialog/textbox.d \
./scripts/lxdialog/util.d \
./scripts/lxdialog/yesno.d 


# Each subdirectory must supply rules for building sources it contributes
scripts/lxdialog/%.o: ../scripts/lxdialog/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/root/workspace1/netio" -I"/root/workspace1/netio/core/portio" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


