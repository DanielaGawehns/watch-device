/**
 * Low-level networking code
 * TODO: Add openSSL
 * @author Peter Bosch <me@pbx.sh>
 */
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <dlog.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "sensorbasicui"

#if !defined(PACKAGE)
#define PACKAGE "org.example.sensorbasicui"
#endif

int                udp_sock;
int                ulst_sock;
int                clnt_sock;
struct sockaddr_in bcast_addr;
struct sockaddr_in any_addr;
struct sockaddr_in srv_addr;
const char *       srv_ident = "WatchSrvrPing";

void network_init() {

    bcast_addr.sin_family = AF_INET;
    bcast_addr.sin_port = (in_port_t)htons(2112);
    bcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

     any_addr.sin_family = AF_INET;
     any_addr.sin_port = (in_port_t)htons(2113);
     any_addr.sin_addr.s_addr = htonl(INADDR_ANY);

}

void ulst_init() {
	int bc_enable, r;
    struct sockaddr_in s;
    struct timeval timeout;

	ulst_sock = socket( AF_INET, SOCK_DGRAM, 0 );

	if ( ulst_sock < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to open UDP socket: %s (%i)",
				strerror(errno), errno);
		return;
	}

	r = fcntl( ulst_sock, F_SETFL, 0 );

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to blocking mode: %s (%i)",
				strerror(errno), errno);
		close( ulst_sock );
		return;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 750000;

	bc_enable = 1;


	r = setsockopt(ulst_sock, SOL_SOCKET, SO_BROADCAST, &bc_enable, sizeof bc_enable);

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to enable broadcast: %s (%i)",
				strerror(errno), errno);
		close( ulst_sock );
		return;
	}

	r = setsockopt( ulst_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set timeout: %s (%i)",
				strerror(errno), errno);
		close( ulst_sock );
		return;
	}

	r = bind( ulst_sock, &any_addr, sizeof any_addr );

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to bind UDP socket: %s (%i)",
					strerror(errno), errno);
		return;
	}

}

void broadcast_init() {
	int bc_enable, r;
    struct sockaddr_in s;
    struct timeval timeout;

	udp_sock = socket( AF_INET, SOCK_DGRAM, 0 );

	if ( udp_sock < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to open UDP socket: %s (%i)",
				strerror(errno), errno);
		return;
	}

	bc_enable = 1;


	r = setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &bc_enable, sizeof bc_enable);

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to enable broadcast: %s (%i)",
				strerror(errno), errno);
		close( udp_sock );
		return;
	}

}

void broadcast_send() {

	const char *mess = "HelloWorld!"; //TODO: What do we send here

    if(sendto( udp_sock, mess, strlen(mess), 0, &bcast_addr, sizeof bcast_addr ) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send broadcast: %s (%i)",
				strerror(errno), errno);
		close( udp_sock );
		return;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Sent broadcast");

}

int broadcast_recv() {
	ssize_t rsz;
	char buf[128];
	socklen_t len = sizeof srv_addr;
	for ( ;; ) {
		/* Receive a single datagram from the server */
		rsz = recvfrom( ulst_sock, buf, sizeof buf - 1, 0, &srv_addr, &len );
		if ( rsz < 0 ) {
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to receive server address: %s (%i)",
					strerror(errno), errno);
			return -1;
		}
		buf[rsz] = 0;
		if ( rsz == 0 || 0 != strncmp( buf, srv_ident, sizeof buf - 1 ) ) {
			dlog_print(DLOG_WARN, LOG_TAG, "Received invalid ack: %s", buf);
			continue;
		}
		break;
	}
	dlog_print(DLOG_INFO, LOG_TAG, "Acked by server at %s", inet_ntoa(srv_addr.sin_addr));
    srv_addr.sin_port = (in_port_t)htons(2114);
	return 0;
}

void broadcast_stop() {
	close( ulst_sock );
    close( udp_sock );
}

int broadcast_hello() {
	int s;
	network_init();
	ulst_init();
	broadcast_init();
	broadcast_send();
	s = broadcast_recv();
	broadcast_stop();
	if ( s < 0 )
		return -1;
}

int client_connect() {
	int r;
    struct timeval timeout;
	clnt_sock = socket( AF_INET, SOCK_STREAM, 0 );

	if ( clnt_sock < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to open TCP socket: %s (%i)",
				strerror(errno), errno);
		return -1;
	}

	r = fcntl( clnt_sock, F_SETFL, 0 );

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to blocking mode: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 750000;

	r = setsockopt( clnt_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set timeout: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	r = connect( clnt_sock, &srv_addr, sizeof srv_addr );

	if ( r < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to connect TCP socket: %s (%i)",
					strerror(errno), errno);
		return -1;
	}

	return 0;

}


void client_close() {
	close( clnt_sock );
}

int client_write( const void *data, size_t size ) {
	ssize_t ws, off;
	for ( off = 0; off < size; off += ws ) {
		ws = send( clnt_sock, data + off, size - off, 0 );
		if ( ws < 0 ) {
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send data over TCP: %s (%i)",
					strerror(errno), errno);
			close( clnt_sock );
			return -1;
		}
	}
	return 0;
}

int client_available( ) {
	int av, r;
	r = ioctl( clnt_sock, FIONREAD, &av );
	//TODO: Handle error
	return av;
}


/**
 * 
 *
 *
 */
int client_read( void *data, size_t size ) {
	ssize_t ws, off;
	for ( off = 0; off < size; off += ws ) {
		ws = recv( clnt_sock, data + off, size - off, 0 );
		if ( ws < 0 ) {
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to receive data over TCP: %s (%i)",
					strerror(errno), errno);
			close( clnt_sock );
			return -1;
		}
	}
	return 0;
}

