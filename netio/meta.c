/* This file has been generated automatically.
   Please do not modify it, edit the m4 scripts instead. */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdint.h>
#include "config.h"

#if ARCH == ARCH_HOST
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "core/host/tap.h"
#include "core/host/stdin.h"

/* for C-c exit handler */
#include <signal.h>
#include <stdlib.h>
void ethersex_meta_exit (int signal);

#endif

void dyndns_update();
void periodic_process();
extern uint8_t bootload_delay;
volatile uint8_t newtick;

#include "network.h"
#include "core/debug.h"
#include "core/periodic.h"
#include "hardware/ethernet/enc28j60.h"
#include "hardware/radio/rfm12/rfm12.h"
#include "hardware/radio/rfm12/rfm12.h"
#include "protocols/uip/uip.h"
#include "protocols/uip/uip_router.h"
#include "protocols/uip/uip_arp.h"
#include "protocols/dns/resolv.h"
void
ethersex_meta_init (void)
{
#if ARCH == ARCH_HOST
    signal(SIGINT, ethersex_meta_exit);
#endif

    network_init ();
    periodic_init ();
    rfm12_init ();
}  /* End of ethersex_meta_init. */

void
ethersex_meta_netinit (void)
{
#   if defined(DYNDNS_SUPPORT) && !defined(BOOTP_SUPPORT) \
      && ((!defined(IPV6_SUPPORT)) || defined(IPV6_STATIC_SUPPORT))
    dyndns_update();
#   endif

    init_enc28j60 ();
    resolv_init ();
} /* End of ethersex_meta_netinit. */

#if ARCH == ARCH_HOST
void
ethersex_meta_exit (int signal)
{
    if (signal != SIGINT) return;
    printf ("Shutting down Ethersex ...\n");
    exit(0);
} /* End of ethersex_meta_exit. */
#endif  /* ARCH == ARCH_HOST */


void
ethersex_meta_startup (void)
{

}  /* End of ethersex_meta_startup. */

void
ethersex_meta_mainloop (void)
{

    debug_process_uart (); wdt_kick ();
    network_process (); wdt_kick ();
    rfm12_int_process (); wdt_kick ();
    rfm12_process (); wdt_kick ();
    periodic_process(); wdt_kick();
#ifdef CPU_SLEEP
/* Works only if there are interrupts enabled, e.g. from periodic.c */
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_mode();
#endif
}


void periodic_process(void)
{
    static uint16_t counter = 0;
#if ARCH == ARCH_HOST
    {
	fd_set fds;
	struct timeval tv = { .tv_sec = 0, .tv_usec = 20000 };

	FD_ZERO (&fds);
#ifdef ECMD_PARSER_SUPPORT
	FD_SET (0, &fds);
#endif  /* ECMD_PARSER_SUPPORT */
	FD_SET (tap_fd, &fds);
	select (tap_fd + 1, &fds, NULL, NULL, &tv);

#ifdef ECMD_PARSER_SUPPORT
	if (FD_ISSET (0, &fds))
	   stdin_read ();
#endif  /* ECMD_PARSER_SUPPORT */

	if (FD_ISSET (tap_fd, &fds))
	   tap_read ();

#else
    if (newtick) {
        newtick=0;
#endif
        counter++;
#ifdef UIP_SUPPORT
        if (uip_buf_lock ()) {
#ifdef RFM12_IP_SUPPORT
           _uip_buf_lock --;
           if (uip_buf_lock ()) {
             return;           /* hmpf, try again shortly
                                   (let's hope we don't miss too many ticks */
           }
           else {
               rfm12_status = RFM12_OFF;
               rfm12_rxstart();
           }
#else
           return;
#endif
        }
#endif


if (counter % 1 == 0) {

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
;
}

if (counter % 10 == 0) {
 
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
  
;
}

if (counter % 50 == 0) {
enc28j60_periodic();
}

if (counter % 500 == 0) {
counter = 0;
uip_arp_timer();
}


#ifdef  UIP_SUPPORT
   uip_buf_unlock ();
#endif

#       ifdef BOOTLOADER_SUPPORT
        if(bootload_delay)
            if(-- bootload_delay == 0) {
		cli();
		_IVREG = _BV(IVCE);	        /* prepare ivec change */
		_IVREG = 0x00;                  /* change ivec */

		#ifdef USE_WATCHDOG
			wdt_disable();
		#endif
		
                void (*jump_to_application)(void) = NULL;
                jump_to_application();
            }
#       endif
    }
}
