#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "network.h"
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

extern int    clnt_sock;
extern struct sockaddr_in srv_addr;

void client_init() {
}


unsigned int fffff(char *str)
{
    int a, b, c, d;
    char arr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
    return *(unsigned int *)arr;
}

int client_connect() {
	srv_addr.sin_family = AF_INET;
srv_addr.sin_port = htons(2114);
srv_addr.sin_addr.s_addr = fffff("192.168.1.110");


	int r;
    struct timeval timeout;
	clnt_sock = socket( AF_INET, SOCK_STREAM, 0 );

	if ( clnt_sock < 0 ) {
		net_log_err( "Failed to open TCP socket: %s (%i)",
				strerror(errno), errno);
		return -1;
	}

	r = fcntl( clnt_sock, F_SETFL, 0 );

	if ( r < 0 ) {
		net_log_err( "Failed to blocking mode: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 750000;

	r = setsockopt( clnt_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	if ( r < 0 ) {
		net_log_err( "Failed to set timeout: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	r = connect( clnt_sock, 
	             (struct sockaddr *) &srv_addr, sizeof srv_addr );

	if ( r < 0 ) {
		net_log_err( "Failed to connect TCP socket: %s (%i)",
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
			net_log_err( "Failed to send data over TCP: %s (%i)",
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
		if ( ws < 0 && errno != EAGAIN ) {
			net_log_err( "Failed to receive data over TCP: %s (%i)",
					strerror(errno), errno);
			close( clnt_sock );
			return -1;
		} else if ( ws < 0 )
			ws = 0;
	}
	return 0;
}

