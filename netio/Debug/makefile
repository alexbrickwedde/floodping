################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include services/wol/subdir.mk
-include services/watchcat/subdir.mk
-include services/watchasync/subdir.mk
-include services/vnc/subdir.mk
-include services/upnp/subdir.mk
-include services/tftp/subdir.mk
-include services/stella/subdir.mk
-include services/pam/subdir.mk
-include services/ntp/subdir.mk
-include services/motd/subdir.mk
-include services/moodlight/subdir.mk
-include services/jabber/subdir.mk
-include services/httpd/subdir.mk
-include services/glcdmenu/menu-interpreter/subdir.mk
-include services/glcdmenu/subdir.mk
-include services/echo/subdir.mk
-include services/dyndns/subdir.mk
-include services/curtain/subdir.mk
-include services/cron/subdir.mk
-include services/clock/subdir.mk
-include services/bulbdial/subdir.mk
-include services/appsample/subdir.mk
-include scripts/lxdialog/subdir.mk
-include protocols/zbus/subdir.mk
-include protocols/yport/subdir.mk
-include protocols/ustream/subdir.mk
-include protocols/usb/usbdrv/subdir.mk
-include protocols/usb/subdir.mk
-include protocols/uip/subdir.mk
-include protocols/udpstella/subdir.mk
-include protocols/udpcurtain/subdir.mk
-include protocols/udpIO/subdir.mk
-include protocols/twitter/subdir.mk
-include protocols/to1/subdir.mk
-include protocols/syslog/subdir.mk
-include protocols/soap/subdir.mk
-include protocols/snmp/subdir.mk
-include protocols/smtp/subdir.mk
-include protocols/sms77/subdir.mk
-include protocols/serial_line_log/subdir.mk
-include protocols/nmea/subdir.mk
-include protocols/netstat/subdir.mk
-include protocols/mysql/subdir.mk
-include protocols/msr1/subdir.mk
-include protocols/modbus/subdir.mk
-include protocols/mdns_sd/subdir.mk
-include protocols/irc/subdir.mk
-include protocols/httplog/subdir.mk
-include protocols/ecmd/via_usart/subdir.mk
-include protocols/ecmd/via_udp/subdir.mk
-include protocols/ecmd/via_tcp/subdir.mk
-include protocols/ecmd/via_i2c/subdir.mk
-include protocols/ecmd/sender/subdir.mk
-include protocols/ecmd/subdir.mk
-include protocols/dns/subdir.mk
-include protocols/dmx/subdir.mk
-include protocols/cw/subdir.mk
-include protocols/bootp/subdir.mk
-include protocols/artnet/subdir.mk
-include mcuf/subdir.mk
-include mcuf/image/subdir.mk
-include mcuf/borg-16/subdir.mk
-include hardware/zacwire/subdir.mk
-include hardware/ultrasonic/subdir.mk
-include hardware/storage/sd_reader/subdir.mk
-include hardware/storage/dataflash/subdir.mk
-include hardware/sram/subdir.mk
-include hardware/sms/subdir.mk
-include hardware/sht/subdir.mk
-include hardware/radio/rfm12/subdir.mk
-include hardware/radio/fs20/subdir.mk
-include hardware/pwm/subdir.mk
-include hardware/onewire/subdir.mk
-include hardware/lcd/s1d15g10/subdir.mk
-include hardware/lcd/s1d13305/subdir.mk
-include hardware/lcd/subdir.mk
-include hardware/lcd/ST7626/subdir.mk
-include hardware/isdn/subdir.mk
-include hardware/ir/rc5/subdir.mk
-include hardware/io_expander/subdir.mk
-include hardware/input/ps2/subdir.mk
-include hardware/input/subdir.mk
-include hardware/input/buttons/subdir.mk
-include hardware/i2c/slave/subdir.mk
-include hardware/i2c/master/subdir.mk
-include hardware/hbridge/subdir.mk
-include hardware/ethernet/subdir.mk
-include hardware/dac/subdir.mk
-include hardware/clock/dcf77/subdir.mk
-include hardware/camera/subdir.mk
-include hardware/avr/subdir.mk
-include hardware/adc/subdir.mk
-include hardware/adc/kty/subdir.mk
-include hardware/adc/ads7822/subdir.mk
-include embed/subdir.mk
-include core/vfs/subdir.mk
-include core/util/subdir.mk
-include core/subdir.mk
-include core/tty/subdir.mk
-include core/portio/subdir.mk
-include core/host/subdir.mk
-include core/gui/subdir.mk
-include core/crypto/subdir.mk
-include control6/subdir.mk
-include contrib/zbus-serial-host/subdir.mk
-include contrib/webscripts/subdir.mk
-include contrib/usb_net/subdir.mk
-include contrib/udpCurtain/subdir.mk
-include contrib/mcuf/subdir.mk
-include contrib/libecmd/rfm12ask_2272/subdir.mk
-include contrib/libecmd/interactive/subdir.mk
-include contrib/kty81-110/subdir.mk
-include contrib/ecmd_usb/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
netio.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: netio.elf secondary-outputs

# Tool invocations
netio.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,netio.map -mmcu=atmega644p -o "netio.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

netio.lss: netio.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S netio.elf  >"netio.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: netio.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644p netio.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) netio.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
