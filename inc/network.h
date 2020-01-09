/*
 * network.h
 *
 *  Created on: Nov 27, 2019
 *      Author: pbx
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdlib.h>

void network_init();
void ulst_init( );
void broadcast_init( );
void broadcast_send( );
int broadcast_recv( );
void broadcast_stop( );
void broadcast_hello( );
int client_connect( );
void client_close( );
int client_write( const void *data, size_t size );
int client_available( );
int client_read( void *data, size_t size );


#endif /* NETWORK_H_ */
