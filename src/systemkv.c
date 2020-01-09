
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "keyval.h"
#include "protocol.h"

keyval *kv_sys;

int uid_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	return prot_create_param_1s( status, nparam, param, "WatchUID!2" );
}

void init_syskv()
{
	keyval_init();
	kv_sys = keyval_create_ns( "system" );
	keyval *uid = keyval_create_leaf( "uid", "string", uid_get, NULL, NULL );
	assert( keyval_add_p( "", kv_sys ) == 0 );
	assert( keyval_add_p( "system", uid ) == 0 );

}
