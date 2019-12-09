/*
 * protocol.h
 *
 *  Created on: Dec 6, 2019
 *      Author: pbx
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdlib.h>
#include <stdargs.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
	int16_t length;
	void *data;
} message_param;

#define PROTOCOL_VERSION (1)
#define MESSAGE_PING (0)
#define MESSAGE_PONG (1)
#define MESSAGE_INCREMENT (2)
#define MESSAGE_PLAYBACK (3)
#define MESSAGE_SENSOR_INTERVAL (4)
#define MESSAGE_SENSOR_SETTING (5)
#define MESSAGE_LIVE_INTERVAL (6)

/**
 * Called by the protocol handler when a MESSAGE_SENSOR_INTERVAL comes in
 */
void cmd_sensor_interval( const char *sensor_name, double interval );

/**
 * Called by the protocol handler when a MESSAGE_SENSOR_SETTING comes in.
 */
void cmd_sensor_setting ( const char *sensor_name, const char *setting_name, const void *value, size_t value_size );

/**
 * Called by the protocol handler when a MESSAGE_LIVE_INTERVAL comes in.
 */
void cmd_live_interval  ( double interval );

/**
 *
 */
void prot_printerr( const char *format, va_list list );

/**
 * This function performs the handshake with the host
 * @return 0 when successful. or -1 if not.
 */
int  prot_handshake( );

/**
 * Sends a message
 * @return 0 when successful. or -1 if not.
 */
int  prot_send( int type, int nparam, message_param *param );

/**
 * Frees a message_param struct
 */
void prot_freeparam( int nparam, message_param *param );

/**
 * Receive a message
 * @return 0 when successful. or -1 if not.
 */
int  prot_recv( int *type, int *nparam, message_param **param );

/**
 * Handle incoming packets if any
 */
void prot_process();

#endif /* NETWORK_H_ */
