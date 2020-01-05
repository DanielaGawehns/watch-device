
#include "keyval.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
void print_params( int nparam, message_param *param )
{
	char buf[80];
	int i;
	printf("nparam: %i\n****************\n", nparam);
	for ( i = 0; i < nparam; i++ ) {
		buf[0] = 0;
		if ( param[i].length < 80 ) {
			memcpy( buf, param[i].data, param[i].length );
			buf[ param[i].length ] = 0;
		}
		printf("\t%4i %s\n", param[i].length, buf);
	}
	printf("****************\n");
}

void print_reply( int status, const char *msg ) {
	printf("Status: %4i (%s)\n", status, msg);
}

