/**
 * @file protocol.h
 * @author Peter Bosch <me@pbx.sh>
 * @date Dec 6, 2019
 * @brief implementation of protocol
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
#define MESSAGE_GET_PLAYBACK    (6)

void prot_handle_error();

/**
 * 
 */
void prot_printerr( const char *format, va_list list );

/**
 * This function performs the handshake with the host
 * @return 0 when successful. or -1 if not.
 */
int prot_handshake_send( );

/**
 * This function receives the handshake from the host
 * @return 0 when successful, 1 when delayed or -1 if an error occurred.
 */
int prot_handshake_recv( );

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

/**
 * Sends a reply packet.
 * @param seq    The sequence ID of the packet we are responding to
 * @param status The status code to send
 * @param msg    The status message to send
 * @param nparam The number of parameters to send
 * @param param  The parameters to send
 * @return When succesful, 0. If failure occurred, <0.
 */
int prot_send_reply( int seq, int status, const char *msg, 
                      int nparam, message_param *param );

int prot_send_increment( const char *sensor, double time,
                      int ndata, double *data );

int prot_send_playback( const char *sensor, long long time,
                      int ndata, double *data );

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

/**
 * Sets a param to a long value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_l( message_param *param, long long value );

int prot_create_param_list( char **status, int *nparam, message_param **param );

/**
 * @brief Creates a parameter list with one string parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1s( char **status, 
                          int *nparam, message_param **param, 
                          const char *value );

/**
 * @brief Creates a parameter list with one integer parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1i( char **status, 
                          int *nparam, message_param **param, 
                          int value );

/**
 * @brief Creates a parameter list with one long long parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1l( char **status,
                          int *nparam, message_param **param, 
                          long long value );

/**
 * @brief Creates a parameter list with one double parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1d( char **status, 
                          int *nparam, message_param **param, 
                          double value );

/**
 * @brief Creates a parameter list with two double parameters and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_2d( char **status,
                          int *nparam, message_param **param,
                          double val1, double val2 );

/**
 * Encode a long long to a memory buffer
 */
void prot_encode_long( void *output, long long value );

/**
 * Decode a long long from a memory buffer
 */
long long prot_decode_long( const void *output );

/**
 * Encode an int to a memory buffer
 */
void prot_encode_int( void *output, int value );

/**
 * Decode an int from a memory buffer
 */
int prot_decode_int( const void *output );

/**
 * Encode a double to a memory buffer
 */
void prot_encode_double( void *output, double value );

/**
 * Decode a double from a memory buffer
 */
double prot_decode_double( const void *output );

#endif /* PROTOCOL_H_ */
