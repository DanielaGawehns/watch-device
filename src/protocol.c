
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
#include "network.h"

void prot_error( const char *format, ... ) {

}

int prot_handshake( ) {
	int r;
	char version = PROTOCOL_VERSION, reply = 0;
	r = client_write( &version, sizeof version );
	if ( r < 0 ) {
		return -1;
	}
	r = client_read( &reply, sizeof reply );
	if ( r < 0 ) {
		return -1;
	}
	if ( reply != PROTOCOL_ACK ) {
		prot_error("Bad response: 0x%02X", reply);
		return -1;
	}
	return 0;
}

int prot_send( int type, int nparam, message_param *param ) {
	int r, i;
	char header[2];

	if ( type < 0 || type >= 128 ) {
		prot_error("Tried to send bad message: 0x%02X", type);
		return -1;
	}
	if ( nparam < 0 || nparam >= 128 ) {
		prot_error("Tried to send bad parameter count: 0x%02X", nparam);
		return -1;
	}

	header[0] = (char) type;
	header[1] = (char) nparam;

	r = client_write( header, sizeof header );
	if ( r < 0 )
		return -1;

	for ( i = 0; i < nparam; i++ ) {
		el = param[i].length + 2;
		param[i].length = htons( param[i].length );
		r = client_write( param + i, el );
		if ( r < 0 ) {
			return -1;
		}
		param[i].length = ntohs( param[i].length );
	}

	return 0;

}

void prot_freeparam( int nparam, message_param *param ){
	int i;
	for ( i = 0; i < nparam; i++ ) {
		if ( param[i].data )
			free( param[i].data )
	}
	free( param );
}

int prot_recv( int *type, int *nparam, message_param **param ) {
	int r, i;
	char header[2];
	int16_t size;

	r = client_read( header, sizeof header );
	if ( r < 0 ) {
		prot_error("Error during receive");
		return -1;
	}

	*type = header[0] & 0xff;
	*nparam = header[1] & 0xff;

	*param = malloc( nparam * sizeof(message_param) );
	if ( !*param ) {
		return -1;
	}
	memset( *param, 0,  nparam * sizeof(message_param) );

	for ( i = 0; i < *nparam; i++ ) {
		r = client_read( &size, sizeof size );
		if ( r < 0 ) {
			prot_freeparam( *nparam, *param );
			return -1;
		}
		size = ntohs(size);

		(*param)[i].length = size;
		(*param)[i].data = malloc( size + 1 );
		if (!(*param)[i].data) {
			prot_freeparam( *nparam, *param );
			return -1;
		}
		memset( (*param)[i].data, 0, size + 1 );

		r = client_read( (*param)[i].data, size );
		if ( r < 0 )
			prot_freeparam( *nparam, *param );
			return -1;
		}
	}

	return 0;

}

void prot_process() {
	int type, nparam;
	message_param *param;

	if ( client_available() < 2 )
		return;

	r = prot_recv(&type, &nparam, &param);
	if ( r < 0 ) {
		prot_error("Error during protocol receive");
		return;
	}

	switch( type ) {
	case MESSAGE_PING:
		prot_send(MESSAGE_PONG, nparam, param);
		break;
	case MESSAGE_PONG:

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
