#include <string.h>
#include <errno.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "sensorbasicui"

#if !defined(PACKAGE)
#define PACKAGE "org.example.sensorbasicui"
#endif

#include <arpa/inet.h>
#include "network.h"
#include "protocol.h"

void prot_error( const char *format, ... ) {

}

/**
 * This function performs the handshake with the host
 * @return 0 when successful. or -1 if not.
 */
int prot_handshake( ) {
	int r;
	char version = PROTOCOL_VERSION, reply = 0;

	/* Try to send the version code */
	r = client_write( &version, sizeof version );
	if ( r < 0 ) {
		return -1;
	}

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
	int r, i, el;
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
	header.seq    = htons( type );
	header.opcode = (char) nparam;
	header.nparam = (char) nparam;

	/* Send the header */
	r = client_write( &header, sizeof header );
	if ( r < 0 )
		return -1;

	/* Send the parameters */
	for ( i = 0; i < nparam; i++ ) {

		/* Compute the length for the param structure */
		el = param[i].length + 2;

		/* Convert the length field to network endianness */
		/* (We're reusing the input structure to construct the network
         *  structure for the parameter so we need to convert this back
         *  later, for otherwise the caller will see an invalid value
         *  there. */
		param[i].length = htons( param[i].length );

		/* Send the packet */
		r = client_write( param + i, el );
		if ( r < 0 ) {
			return -1;
		}

		/* Restore the length field */
		param[i].length = ntohs( param[i].length );

	}

	return 0;

}

/**
 * Frees a message_param struct
 */
void prot_freeparam( int nparam, message_param *param ){
	int i;
	/* Iterate over the parameters */
	for ( i = 0; i < nparam; i++ ) {
		/* Check if the data pointer is set */
		if ( param[i].data ) {
			/* If so, free the data buffer */
			free( param[i].data )
		}
	}
	free( param );
}

/**
 * Receive a message
 * @return 0 when successful. or -1 if not.
 */
int prot_recv( int *seq, int *type, int *nparam, message_param **param ) {
	int r, i;
	message_param header;
	int16_t size;

	r = client_read( &header, sizeof header );
	if ( r < 0 ) {
		return -1;
	}

	/* Decode the header fields */
	*type   = header.type   & 0xFF;
	*nparam = header.nparam & 0xFF;
	*seq    = ntohs( header.seq ) & 0xFFFF;

	/* Allocate the parameter header structure */
	*param = malloc( nparam * sizeof(message_param) );
	if ( !*param ) {
		prot_error("Could not allocate parameter list");
		return -1;
	}

	/* Zero it */
	memset( *param, 0,  nparam * sizeof(message_param) );

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

/**
 * Handle incoming packets if any
 */
void prot_process() {
	int seq, type, nparam;
	message_param *param;

	/* Do we have at least a full header available? */
	if ( client_available() < 4 )
		return;

	/* Receive the packet */
	r = prot_recv(&seq, &type, &nparam, &param);
	if ( r < 0 ) {
		prot_error("Error during protocol receive");
		return;
	}

	switch( type ) {
	case MESSAGE_PING:
		prot_send(MESSAGE_PONG, nparam, param);
		break;

	case MESSAGE_REPLY:
		/* Should not arrive like this? (at the watch side) */
		break;

	case MESSAGE_SENSOR_INTERVAL:
		if ( nparam != 2 ) {
			prot_error("Mismatched parameter count for MESSAGE_SENSOR_INTERVAL: %i", nparam);
			break;
		}
		if ( param[1].size != 8 ) {
			prot_error("Mismatched parameter 1 size for MESSAGE_SENSOR_INTERVAL: %i", param[1].size);
			break;
		}
		cmd_sensor_interval( (const char *) param[0].data, &(double *)param[1].data );
		break;

	case MESSAGE_SENSOR_SETTING:
		if ( nparam != 3 ) {
			prot_error("Mismatched parameter count for MESSAGE_SENSOR_SETTING: %i", nparam);
			break;
		}
		cmd_sensor_setting( (const char *) param[0].data, (const char *)param[1].data, param[2].data, param[2].length );
		break;

	case MESSAGE_LIVE_INTERVAL:
		if ( nparam != 1 ) {
			prot_error("Mismatched parameter count for MESSAGE_LIVE_INTERVAL: %i", nparam);
			break;
		}
		if ( param[0].size != 8 ) {
			prot_error("Mismatched parameter 0 size for MESSAGE_LIVE_INTERVAL: %i", param[0].size);
			break;
		}
		cmd_live_interval( &(double *)param[0].data );
		break;

	default:
		prot_error("Unknown message: %i", nparam);
		break;
	}

	prot_freeparam( nparam, param );

}

int rep_data( int type, const char *name, double time, int ndata, double *data ) {
	message_param *param;
	int nparam;

	nparam = 1 + ndata;

	param = malloc( nparam * sizeof(message_param) );
	if (!param) {
		prot_error("Failed to allocate packet buffers");
		return -1;
	}

	param[0].data = name;
	param[0].length = strlen( name );

	param[1].data = &time;
	param[1].length = sizeof
	for ( i = 0; i < ndata; i++ ) {
		param[2+i].data = data + i;
		param[2+i].length = sizeof double;
	}



}



