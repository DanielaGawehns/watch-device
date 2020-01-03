
#if false

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <dlog.h>
#include <unistd.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "sensorbasicui"

#if !defined(PACKAGE)
#define PACKAGE "org.example.sensorbasicui"
#endif

int                udp_sock;
int                lst_sock;
struct sockaddr_in bcast_addr;
struct sockaddr_in lst_addr;

void network_init() {

    bcast_addr.sin_family = AF_INET;
    bcast_addr.sin_port = (in_port_t)htons(2112);
    bcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

}

void broadcast_init() {
	int bc_enable, r, udp_sock;
    struct sockaddr_in s;

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

    if(sendto( udp_sock, mess, strlen(mess), 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send broadcast: %s (%i)",
				strerror(errno), errno);
		close( udp_sock );
		return;
	}

	dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send broadcast: %s (%i)",
			strerror(errno), errno);

}

void broadcast_stop() {

    close( udp_sock );

}

void listener_start() {

	lst_sock = socket( AF_INET, SOCK_STREAM, 0 );

	if ( lst_sock < 0 ) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to open TCP socket: %s (%i)",
				strerror(errno), errno);
		return;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

}

#endif
