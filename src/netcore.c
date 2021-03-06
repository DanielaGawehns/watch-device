/**
 * @file netcore.c
 * @brief ecore implementation of network
 */

#include <Ecore.h> //ecore
#include <dlog.h>
#include "network.h"
#include "protocol.h"

#define STATE_DISCONNECT   (0)
#define STATE_BCAST_START  (1)
#define STATE_BCAST_ACTIVE (2)
#define STATE_CLIENT_CONN  (3)
#define STATE_HANDSHAKE    (4)
#define STATE_ACTIVE       (5)

Ecore_Timer *netcore_timer;
static int netcore_state = STATE_DISCONNECT;
#define LOG_TAG ("sensorbasicui")
void netcore_stop();

/*
* @brief: the main ecore loop, this updates the scheduler by generating the current time and calling scheduler_update
* @params: data data pointer, is not used (is needed because this is an ecore function)
*/
Eina_Bool netcore_process(void *data) {
	int res;
	switch ( netcore_state ) {
	case STATE_DISCONNECT:
		broadcast_stop();
		client_close();
		//netcore_stop();
		netcore_state = STATE_BCAST_START;
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state BCAST_START", __FILE__, __LINE__);
		return 1;
	case STATE_BCAST_START:
		broadcast_stop();
		res = broadcast_start();
		if ( res < 0 ) {
			netcore_state = STATE_DISCONNECT;
	        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
			return 1;
		}
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state BCAST_ACTIVE", __FILE__, __LINE__);
        netcore_state = STATE_BCAST_ACTIVE;
	case STATE_BCAST_ACTIVE:
		res = broadcast_send();
		if ( res < 0 ) {
			netcore_state = STATE_DISCONNECT;
	        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
			return 1;
		}
		res = broadcast_recv();
		if ( res < 0 )
			return 1;
		netcore_state = STATE_CLIENT_CONN;
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state CLIENT_CONN", __FILE__, __LINE__);
	case STATE_CLIENT_CONN:
		broadcast_stop();
		res = client_connect();
		if ( res < 0 ) {
			netcore_state = STATE_DISCONNECT;
	        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
			return 1;
		}
		res = prot_handshake_send();
		if ( res < 0 ) {
			netcore_state = STATE_DISCONNECT;
	        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
			return 1;
		}
		netcore_state = STATE_HANDSHAKE;
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state HANDSHAKE", __FILE__, __LINE__);
	case STATE_HANDSHAKE:
		res = prot_handshake_recv();
		if ( res == 1 )
			return 1;
		if ( res < 0 ) {
			netcore_state = STATE_DISCONNECT;
	        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
			return 1;
		}
		netcore_state = STATE_ACTIVE;
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state ACTIVE", __FILE__, __LINE__);
	case STATE_ACTIVE:
		prot_process();
		return 1;
	}
}

void prot_handle_error()
{
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Network error, goto DISCONNECT", __FILE__, __LINE__);
	netcore_state = STATE_DISCONNECT;
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Enter state DISCONNECT", __FILE__, __LINE__);
}

int netcore_send_increment( const char *sensor, double time,
                      int ndata, double *data ) {
	if ( netcore_state != STATE_ACTIVE )
		return 0;
	return prot_send_increment(sensor, time, ndata, data);
}

/*
* @brief: Stops the network processing timer
*/
void netcore_stop() {
    if( netcore_timer != NULL ){
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Stopping ecore timer for network", __FILE__, __LINE__);
		ecore_timer_del( netcore_timer );
		netcore_timer = NULL;
    }
}


/*
* @brief: Start the network processing timer
*/
void netcore_start_timer() {
	double intervalInSec = 0.05;
    if( netcore_timer == NULL ) {
    	dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Starting network process task", __FILE__, __LINE__, intervalInSec);
        netcore_timer = ecore_timer_add(intervalInSec, netcore_process, NULL);
    }
}

void netcore_init() {
	network_init();
}

int netcore_connect() {
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Start connect netcore", __FILE__, __LINE__);
	netcore_state = STATE_BCAST_START;
	netcore_start_timer();
	return 0;
}
