################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../at90can.c \
../at90can_buffer.c \
../at90can_disable_dyn_filter.c \
../at90can_error_register.c \
../at90can_get_buf_message.c \
../at90can_get_dyn_filter.c \
../at90can_get_message.c \
../at90can_send_buf_message.c \
../at90can_send_message.c \
../at90can_set_dyn_filter.c \
../at90can_set_mode.c \
../can_buffer.c \
../main.c \
../mcp2515.c \
../mcp2515_buffer.c \
../mcp2515_error_register.c \
../mcp2515_get_dyn_filter.c \
../mcp2515_get_message.c \
../mcp2515_read_id.c \
../mcp2515_regdump.c \
../mcp2515_send_message.c \
../mcp2515_set_dyn_filter.c \
../mcp2515_set_mode.c \
../mcp2515_sleep.c \
../mcp2515_static_filter.c \
../mcp2515_write_id.c \
../sja1000.c \
../sja1000_buffer.c \
../sja1000_error_register.c \
../sja1000_get_message.c \
../sja1000_send_message.c \
../sja1000_set_mode.c \
../spi.c 

OBJS += \
./at90can.o \
./at90can_buffer.o \
./at90can_disable_dyn_filter.o \
./at90can_error_register.o \
./at90can_get_buf_message.o \
./at90can_get_dyn_filter.o \
./at90can_get_message.o \
./at90can_send_buf_message.o \
./at90can_send_message.o \
./at90can_set_dyn_filter.o \
./at90can_set_mode.o \
./can_buffer.o \
./main.o \
./mcp2515.o \
./mcp2515_buffer.o \
./mcp2515_error_register.o \
./mcp2515_get_dyn_filter.o \
./mcp2515_get_message.o \
./mcp2515_read_id.o \
./mcp2515_regdump.o \
./mcp2515_send_message.o \
./mcp2515_set_dyn_filter.o \
./mcp2515_set_mode.o \
./mcp2515_sleep.o \
./mcp2515_static_filter.o \
./mcp2515_write_id.o \
./sja1000.o \
./sja1000_buffer.o \
./sja1000_error_register.o \
./sja1000_get_message.o \
./sja1000_send_message.o \
./sja1000_set_mode.o \
./spi.o 

C_DEPS += \
./at90can.d \
./at90can_buffer.d \
./at90can_disable_dyn_filter.d \
./at90can_error_register.d \
./at90can_get_buf_message.d \
./at90can_get_dyn_filter.d \
./at90can_get_message.d \
./at90can_send_buf_message.d \
./at90can_send_message.d \
./at90can_set_dyn_filter.d \
./at90can_set_mode.d \
./can_buffer.d \
./main.d \
./mcp2515.d \
./mcp2515_buffer.d \
./mcp2515_error_register.d \
./mcp2515_get_dyn_filter.d \
./mcp2515_get_message.d \
./mcp2515_read_id.d \
./mcp2515_regdump.d \
./mcp2515_send_message.d \
./mcp2515_set_dyn_filter.d \
./mcp2515_set_mode.d \
./mcp2515_sleep.d \
./mcp2515_static_filter.d \
./mcp2515_write_id.d \
./sja1000.d \
./sja1000_buffer.d \
./sja1000_error_register.d \
./sja1000_get_message.d \
./sja1000_send_message.d \
./sja1000_set_mode.d \
./spi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=7372800UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


