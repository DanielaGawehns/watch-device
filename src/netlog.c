#include <stdio.h>
#include <stdarg.h>
#include <dlog.h> //dlog
#define LOG_TAG "sensorbasicui"

void prot_printerr( const char *format, va_list list ) {
	dlog_vprint(DLOG_INFO, LOG_TAG, format, list);
}

void net_log_err( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	dlog_vprint(DLOG_ERROR, LOG_TAG, fmt, l);
	va_end( l );
}

void net_log_warn( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	dlog_vprint(DLOG_WARN, LOG_TAG, fmt, l);
	va_end( l );
}

void net_log_info( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	dlog_vprint(DLOG_INFO, LOG_TAG, fmt, l);
	va_end( l );
}

