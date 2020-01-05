#include <assert.h>
#include <stdlib.h>
#include "prot_cmds.h"

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_get_values( int seq, const char *path )
{
	assert( !"SHOULD NOT BE CALLED" );
}

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_set_values( int seq, const char *path, int nparam, message_param *param )
{
	assert( !"SHOULD NOT BE CALLED" );
}

