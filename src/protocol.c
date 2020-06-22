/**
 * @file protocol.h
 * @author pbx
 * @date Dec 6, 2019
 * @brief implementation of protocol
 */

#include <string.h>
#include <errno.h>
#include <assert.h>
#include <arpa/inet.h>
#include "network.h"
#include "protocol.h"
#include "prot_cmds.h"

int prot_seq = 0;

void prot_error( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;
	va_start( l, fmt );
	prot_printerr( fmt, l );
	va_end( l );
	prot_handle_error();
}

/**
 * This function performs the handshake with the host
 * @return 0 when successful. or -1 if not.
 */
int prot_handshake_send( ) {
	int r;
	char version = PROTOCOL_VERSION;

	/* Try to send the version code */
	r = client_write( &version, sizeof version );
	if ( r < 0 ) {
		return -1;
	}

	return 0;
}

/**
 * This function receives the handshake from the host
 * @return 0 when successful, 1 when delayed or -1 if an error occurred.
 */
int prot_handshake_recv( ) {
	int r;
	char reply = 0;

	if ( client_available() < 1 )
		return 1;

	/* Try to receive the reply */
	r = client_read( &reply, sizeof reply );
	if ( r < 0 ) {
		return -1;
	}

	/* Verify the reply */
	if ( reply != PROTOCOL_ACK ) {
		prot_error("Bad response: 0x%02X", reply);
		return -1;
	}

	return 0;
}

/**
 * Sends a message
 * @return 0 when successful. or -1 if not.
 */
int prot_send( int seq, int type, int nparam, message_param *param ) {
	int r, i;
	short pl;
	message_header header;

	/* Check for integer overflows in the header fields */
	if ( seq < 0 || seq >= 65536 ) {
		prot_error("Tried to send bad sequence: 0x%02X", type);
		return -1;
	}
	if ( type < 0 || type >= 256 ) {
		prot_error("Tried to send bad message: 0x%02X", type);
		return -1;
	}
	if ( nparam < 0 || nparam >= 256 ) {
		prot_error("Tried to send bad parameter count: 0x%02X", nparam);
		return -1;
	}

	/* Fill the header fields. */
	/* (ntohs converts to network endianness) */
	header.seq    = htons( seq );
	header.opcode = (char) type;
	header.nparam = (char) nparam;

	/* Send the header */
	r = client_write( &header, sizeof header );
	if ( r < 0 )
		return -1;

	/* Send the parameters */
	for ( i = 0; i < nparam; i++ ) {

		/* Convert the length field to network endianness */
		pl = htons( param[i].length );

		/* Send the parameter size */
		r = client_write( &pl, sizeof pl );
		if ( r < 0 ) {
			return -1;
		}

		/* Send the parameter body */
		r = client_write( param[i].data, param[i].length );
		if ( r < 0 ) {
			return -1;
		}

	}

	return 0;

}

/**
 * Receive a message
 * @return 0 when successful. or -1 if not.
 */
int prot_recv( int *seq, int *type, int *nparam, message_param **param ) {
	int r, i;
	message_header header;
	int16_t size;

	r = client_read( &header, sizeof header );
	if ( r < 0 ) {
		return -1;
	}

	/* Decode the header fields */
	*type   = header.opcode & 0xFF;
	*nparam = header.nparam & 0xFF;
	*seq    = ntohs( header.seq ) & 0xFFFF;

	/* Allocate the parameter header structure */
	*param = malloc( *nparam * sizeof(message_param) );
	if ( !*param ) {
		prot_error("Could not allocate parameter list");
		return -1;
	}

	/* Zero it */
	memset( *param, 0, *nparam * sizeof(message_param) );

	/* Receive the parameters */
	for ( i = 0; i < *nparam; i++ ) {

		/* Receive parameter size */
		r = client_read( &size, sizeof size );
		if ( r < 0 ) {
			goto dealloc_params;
		}
		/* Convert it to host endianness */
		size = ntohs(size);

		/* Fill paramater structure */
		(*param)[i].length = size;
		(*param)[i].data = malloc( size + 1 );

		/* If data allocation failed, bail out  */
		if (!(*param)[i].data) {
			prot_error("Could not allocate parameter data");
			goto dealloc_params;
		}
		memset( (*param)[i].data, 0, size + 1 );

		/* Receive data */
		r = client_read( (*param)[i].data, size );
		if ( r < 0 ) {
			goto dealloc_params;
		}
	}

	return 0;

dealloc_params:
	prot_freeparam( *nparam, *param );
	return -1;

}

int prot_send_reply( int seq, int status, const char *msg, 
                      int nparam, message_param *param )
{
	message_param *out_param;
	int out_nparam, r;

	assert( nparam == 0 || param != NULL );

	out_nparam = nparam + 2;

	out_param = malloc( out_nparam * sizeof( message_param ) );
	if ( !out_param ) {
		prot_error("Could not allocate reply parameters");
		return -1;	
	}

	/* Load status parameter */
	r = prot_set_param_i( out_param + 0, status );
	if ( r < 0 )
		goto allocerr;

	/* Load message parameter */
	r = prot_set_param_s( out_param + 1, msg );
	if ( r < 0 )
		goto allocerr;

	/* Copy over parameters */
	if ( nparam )
		memcpy( out_param + 2, param, nparam * sizeof( message_param ) );

	/* Send the packet */ 
	r = prot_send( seq, MESSAGE_REPLY, out_nparam, out_param );

	/* Free the new param list, but only the newly copied data */
allocerr:
	prot_freeparam( 2, out_param );

	if ( r < 0 )
		prot_error("Could not send packet");

	return r;

}

int prot_send_increment( const char *sensor, double time,
                      int ndata, double *data )
{
	message_param *out_param;
	int out_nparam, r, i;

	assert( ndata == 0 || data != NULL );

	out_nparam = ndata + 2;

	out_param = malloc( out_nparam * sizeof( message_param ) );
	if ( !out_param ) {
		prot_error("Could not allocate increment parameters");
		return -1;
	}

	/* Load sensor parameter */
	r = prot_set_param_s( out_param + 0, sensor );
	if ( r < 0 )
		goto allocerr;

	/* Load time parameter */
	r = prot_set_param_d( out_param + 1, time );
	if ( r < 0 )
		goto allocerr;

	/* Copy over parameters */
	for ( i = 0; i < ndata; i++ ) {
		r = prot_set_param_d( out_param + 2 + i, data[i] );
		if ( r < 0 )
			goto allocerr;
	}

	/* Send the packet */
	r = prot_send( 0, MESSAGE_INCREMENT, out_nparam, out_param );

	/* Free the new param list */
allocerr:
	prot_freeparam( out_nparam, out_param );

	if ( r < 0 )
		prot_error("Could not send packet");

	return r;

}

/**
 * Handle incoming packets if any
 */
void prot_process() {
	int seq, type, nparam, r, av;
	message_param *param;

	/* Do we have at least a full header available? */
	av = client_available();
	if ( av == -1 ) {
		prot_error("Error during protocol avail in prot_process()");
		return;
	} else if ( av < 4 )
		return;

	/* Receive the packet */
	r = prot_recv(&seq, &type, &nparam, &param);
	if ( r < 0 ) {
		prot_error("Error during protocol receive in prot_process()");
		return;
	}

	switch( type ) {
	case MESSAGE_PING:
		prot_send_reply( seq, 0, "pong", nparam, param );
		break;

	case MESSAGE_REPLY:
		/* Should not arrive like this? (at the watch side) */
		break;

	case MESSAGE_GET_VALUES:
		if ( nparam != 1 ) {
			prot_error("Mismatched parameter count for MESSAGE_GET_VALUES: %i", nparam);
			break;
		}
		cmd_get_values( seq, (const char *) param[0].data );
		break;

	case MESSAGE_SET_VALUES:
		if ( nparam < 2 ) {
			prot_error("Mismatched parameter count for MESSAGE_SET_VALUES: %i", nparam);
			break;
		}
		cmd_set_values( seq, (const char *) param[0].data, nparam - 1, param + 1 );
		break;

	case MESSAGE_GET_PLAYBACK:
		if ( nparam < 2 ) {
			prot_error("Mismatched parameter count for MESSAGE_GET_PLAYBACK: %i", nparam);
			break;
		}
		cmd_get_playback( seq, prot_decode_long(param[0].data), prot_decode_long(param[1].data) );
		break;

	default:
		prot_error("Unknown message: %i", type);
		break;
	}

	prot_freeparam( nparam, param );

}
