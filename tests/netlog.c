#include <stdio.h>
#include <stdarg.h>

void prot_printerr( const char *format, va_list list ) {
	vprintf( format, list );
	printf("\n");
}

void net_log_err( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	prot_printerr( fmt, l );
	va_end( l );
}

void net_log_warn( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	prot_printerr( fmt, l );
	va_end( l );
}

void net_log_info( const char *fmt, ... ) {
	//TODO: Implement
	va_list l;

	va_start( l, fmt );
	prot_printerr( fmt, l );
	va_end( l );
}

