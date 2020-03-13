#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "prot_cmds.h"

void print_params( int nparam, message_param *param );

void print_reply( int status, const char *msg );

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_get_values( int seq, const char *path )
{
	printf("\n\nGET_VALUES received for \"%s\"\n", path);
	message_param param;
	prot_send_reply( seq, -1, "failure", 0, &param );
}
/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_set_values( int seq, const char *path, int nparam, message_param *param )
{
	printf("\n\nSET_VALUES received for \"%s\"\n", path);
	print_params( nparam, param );
	assert( !"SHOULD NOT BE CALLED" );
}


void cmd_get_playback( int seq, long long time_start, long long time_end ){
	
}
