/**
 * @file keyval_cmds.c
 * @author Peter Bosch <me@pbx.sh>
 * @date Jan 5, 2020
 * @brief parameters
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "prot_cmds.h"
#include "keyval.h"

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_get_values( int seq, const char *path )
{
	char *status = NULL;
	int nparam,s;
	message_param *param = NULL;

	s = keyval_get( path, &status, &nparam, &param );

	if ( !status )
		status = strdup("NULL STATUS MESSAGE!");

	prot_send_reply( seq, s, status, nparam, param );
	
	if ( param )
		prot_freeparam( nparam, param );

	if ( status )
		free( status );

	return;
}

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_set_values( int seq, const char *path, int nparam, message_param *param )
{
	char *status = NULL;
	int s;

	s = keyval_set( path, &status, nparam, param );

	if ( !status )
		status = strdup("NULL STATUS MESSAGE!");

	prot_send_reply( seq, s, status, 0, NULL );

	if ( status )
		free( status );

	return;
}

