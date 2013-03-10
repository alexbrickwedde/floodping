  header(network.h)
  init(network_init)
  header(core/debug.h)
  mainloop(debug_process_uart)
 header(core/periodic.h)
 init(periodic_init)
  block(Miscelleanous)
  ecmd_feature(d, "d ", ADDR, Dump the memory at ADDR (16 bytes).)
  ecmd_feature(fuse, "fuse",,Display current fuse settings)
  ecmd_feature(hostname, "hostname",,Display hostname.)
  block(Resetting the controller)
  ecmd_feature(reset, "reset",,Reset the Ethersex.)
  ecmd_feature(wdreset, "wdreset",,Go into endless loop to trigger a watchdog timeout.)
  block(Resetting the controller)
  ecmd_feature(bootloader, "bootloader",,Call the bootloader.)
  timer(1, `
#       if UIP_CONF_IPV6
        if (counter == 5) {
            // Send a router solicitation every 10 seconds, as long
            // as we only got a link local address.  First time one
            // second after boot 
#           ifndef IPV6_STATIC_SUPPORT
            if(((u16_t *)(uip_hostaddr))[0] == HTONS(0xFE80)) {
                uip_router_send_solicitation();
                transmit_packet();
            }
#           endif
        }
#       endif // UIP_CONF_IPV6 
')
  header(hardware/ethernet/enc28j60.h)
  net_init(init_enc28j60)
  mainloop(network_process)
  timer(50, enc28j60_periodic())
 header(hardware/radio/rfm12/rfm12.h)
 mainloop(rfm12_int_process)
 init(rfm12_init)
  header(hardware/radio/rfm12/rfm12.h)
  mainloop(rfm12_process)
  header(protocols/uip/uip.h)
  header(protocols/uip/uip_router.h)
  timer(10, ` 
#       if UIP_CONNS <= 255
            uint8_t i;
#       else
            uint16_t i;
#endif

#           if UIP_TCP == 1
            for (i = 0; i < UIP_CONNS; i++) {
		uip_stack_set_active(uip_conns[i].stack);
                uip_periodic(i);

                // if this generated a packet, send it now 
                if (uip_len > 0)
		    router_output();
            }
#           endif // UIP_TCP == 1

#           if UIP_UDP == 1
            // check udp connections every time 
            for (i = 0; i < UIP_UDP_CONNS; i++) {
		uip_stack_set_active(uip_udp_conns[i].stack);
                uip_udp_periodic(i);

                // if this generated a packet, send it now
                if (uip_len > 0)
		    router_output();
            }
#           endif
  
')
  header(protocols/uip/uip_arp.h)
  timer(500, uip_arp_timer())
  header(protocols/dns/resolv.h)
  net_init(resolv_init)
  block(DNS Resolver)
  ecmd_feature(nslookup, "nslookup ", HOSTNAME, Do DNS lookup for HOSTNAME (call twice).)
  ecmd_feature(dns_server, "dns server", [IPADDR], Display/Set the IP address of the DNS server to use to IPADDR.)
