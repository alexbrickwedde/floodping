################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/pwm/pwm.c \
../hardware/pwm/pwm_dtmf.c \
../hardware/pwm/pwm_freq.c \
../hardware/pwm/pwm_melody.c \
../hardware/pwm/pwm_servo.c \
../hardware/pwm/pwm_servo_ecmd.c \
../hardware/pwm/pwm_wav.c 

OBJS += \
./hardware/pwm/pwm.o \
./hardware/pwm/pwm_dtmf.o \
./hardware/pwm/pwm_freq.o \
./hardware/pwm/pwm_melody.o \
./hardware/pwm/pwm_servo.o \
./hardware/pwm/pwm_servo_ecmd.o \
./hardware/pwm/pwm_wav.o 

C_DEPS += \
./hardware/pwm/pwm.d \
./hardware/pwm/pwm_dtmf.d \
./hardware/pwm/pwm_freq.d \
./hardware/pwm/pwm_melody.d \
./hardware/pwm/pwm_servo.d \
./hardware/pwm/pwm_servo_ecmd.d \
./hardware/pwm/pwm_wav.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/pwm/%.o: ../hardware/pwm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


