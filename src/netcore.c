
#include <Ecore.h> //ecore
#include <dlog.h>
#include "network.h"
#include "protocol.h"
#define LOG_TAG "sensorbasicui"

Ecore_Timer *netcore_timer;

/*
* @brief: the main ecore loop, this updates the scheduler by generating the current time and calling scheduler_update
* @params: data data pointer, is not used (is needed because this is an ecore function)
*/
Eina_Bool netcore_process(void *data) {
	prot_process();
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


int netcore_connect() {
	int status;
	status = broadcast_hello();
	if ( status < 0 )
		return status;
	status = client_connect();
	if ( status < 0 )
		return status;
	status = prot_handshake();
	if ( status < 0 )
		return status;
	netcore_start_timer();
}
