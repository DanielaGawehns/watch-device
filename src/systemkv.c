#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <device/battery.h>
#include "keyval.h"
#include "protocol.h"

keyval *kv_sys;

static char unique_id[40];

/**
 * Polls the watch MAC address and sets it as the unique ID.
 * If this fails, the UID is set to ErrorAssigningUID.
 */
static void generate_uid()
{
	int sock;
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];

    unsigned char *mac_addr;
    int success = 0;

    /* Fill fallback value */
    strcpy( unique_id, "ErrorAssigningUID" );

    /* Open socket to query NIC settings */
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if ( sock == -1 )
    	goto error_ret;

    /* Wrap buffer in descriptor and request interface config */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
    	goto error_cleanup;

    /* Compute list limits */
    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    /* Iterate over the system's network interfaces */
    for (; it != end; ++it) {

    	/* Query the interface flags */
        strcpy(ifr.ifr_name, it->ifr_name);
        if ( ioctl(sock, SIOCGIFFLAGS, &ifr) != 0 )
        	continue;

        /* Ignore loopback interfaces */
        if ( ifr.ifr_flags & IFF_LOOPBACK )
          	continue;

        /* Request the hardware (MAC) address */
        if ( ioctl(sock, SIOCGIFHWADDR, &ifr) != 0 )
        	continue;

        /* Format it as a hex string and accept */
        mac_addr = ifr.ifr_hwaddr.sa_data;
        snprintf( unique_id, 40,
        		"%02X%02X%02X%02X%02X%02X",
        		mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5] );
        break;
    }

cleanup:
	/* Close the socket we used. */
	close( sock );
	return;

error_cleanup:
	close( sock );
error_ret:
	printf("Could not find MAC address: %s (%i)\n", strerror(errno), errno );
	return;
}

/**
 * system.uid getter, see keyval.h
 */
static int uid_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	return prot_create_param_1s( status, nparam, param, unique_id );
}

/**
 * system.battery getter, see keyval.h
 */
static int battery_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	int err, perc = 0;
	err = device_battery_get_percent( &perc );
	if ( err ) {
		*status = strdup( "Error querying battery" );
		*nparam = 0;
		return KV_EINVAL;
	}
	return prot_create_param_1i( status, nparam, param, perc );
}

/**
 * Initialize system namesapce for the key value store
 */
void init_syskv()
{
	keyval_init();
	generate_uid();
	kv_sys = keyval_create_ns( "system" );
	assert( keyval_add_p( "", kv_sys ) == 0 );
	assert( keyval_create_add_k_leaf( kv_sys, "uid", "string", uid_get, NULL, NULL ) != NULL );
	assert( keyval_create_add_k_leaf( kv_sys, "battery", "int", battery_get, NULL, NULL ) != NULL );

}
