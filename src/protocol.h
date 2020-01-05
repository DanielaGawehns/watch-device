/*
 * protocol.h
 *
 *  Created on: Dec 6, 2019
 *      Author: pbx
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>


/**
 * Packet header structure
 */
typedef struct __attribute__((packed)) {
    /**
     * Sequence ID
     */
	uint16_t seq;
    /**
     * Packet ID
     */
	uint8_t  opcode;
	/**
     * Number of message_param structures following this header
     */
	uint8_t  nparam;
} message_header;

/**
 * Parameter structure for network protocol
 */
typedef struct __attribute__((packed)) {
	uint16_t length;
	void *   data;
} message_param;

#define PROTOCOL_VERSION (1)

#define PROTOCOL_ACK (0x06)

#define MESSAGE_PING            (0)
#define MESSAGE_REPLY           (1)
#define MESSAGE_GET_VALUES      (2)
#define MESSAGE_SET_VALUES      (3)
#define MESSAGE_INCREMENT       (4)
#define MESSAGE_PLAYBACK        (5)

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
int  prot_send( int seq, int type, int nparam, message_param *param );

/**
 * Frees a message_param struct
 */
void prot_freeparam( int nparam, message_param *param );

/**
 * Receive a message
 * @return 0 when successful. or -1 if not.
 */
int  prot_recv( int *seq, int *type, int *nparam, message_param **param );

/**
 * Handle incoming packets if any
 */
void prot_process();

int prot_send_reply( int seq, int status, const char *msg, 
                      int nparam, message_param *param );

/**
 * Sets a param to an integer value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_i( message_param *param, int value );

/**
 * Sets a param to a double value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_d( message_param *param, double value );

/**
 * Sets a param to a string value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_s( message_param *param, const char *value );

#endif /* NETWORK_H_ */
