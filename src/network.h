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
int broadcast_hello( );
int client_connect( );
void client_close( );
int client_write( const void *data, size_t size );

/**
 * Polls the number of bytes
 */
int client_available( );

/**
 * Read data from the network connection
 * @param data The buffer to fill with data
 * @param size The number of bytes to read
 * @return 0
 */
int client_read( void *data, size_t size );

void net_log_err( const char *fmt, ... );
void net_log_warn( const char *fmt, ... );
void net_log_info( const char *fmt, ... );

#endif /* NETWORK_H_ */
