/* This file has been generated automatically.
   Please do not modify it, edit the m4 scripts instead. */

#include "core/pt/pt.h"
#ifndef _META_H
#define _META_H

#include "protocols/ecmd/via_tcp/ecmd_state.h"
#include "services/httpd/httpd_state.h"
/* uip appstate for udp */
typedef union uip_udp_connection_state {
#   ifdef CONTROL6_SUPPORT
    struct {
	struct pt pt;
    } control6_udp;
#   endif

} uip_udp_appstate_t; /* end of appstate for udp */

/* uip appstate for tcp */
typedef union uip_tcp_connection_state {
#   ifdef CONTROL6_SUPPORT
    struct {
	struct pt pt;
	lc_t rexmit_lc;
    } control6_tcp;
#   endif

    struct ecmd_connection_state_t ecmd;
    struct httpd_connection_state_t httpd;
} uip_tcp_appstate_t; /* end of tcp appstate */

#endif /* _META_H */

