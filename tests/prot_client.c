
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "keyval.h"
#include "protocol.h"
keyval test;
keyval test_a;
keyval test_b;
void print_params( int nparam, message_param *param );

void print_reply( int status, const char *msg );

int uid_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	return prot_create_param_1s( status, nparam, param, "WatchUID!2" );
}

void init_kv()
{
	keyval_init();
	test.type = "namespace";
	test.name = "system";
	keyval *uid = keyval_create_leaf( "uid", "string", uid_get, NULL, NULL );
	test_b.type = "string";
	test_b.name = "b";
	assert( keyval_add_p( "", &test ) == 0 );
	assert( keyval_add_p( "system", uid ) == 0 );
	assert( keyval_add_p( "system", &test_b ) == 0 );
	
}

void test_get( const char *path ) {
	char *msg;
	int s;
	int nparam;
	message_param *param;
	printf("\n\ntest_get(\"%s\");\n", path);
	s = keyval_get( path, &msg, &nparam, &param );
	print_reply( s, msg );
	print_params( nparam, param );
}

int main( int argc, char **test )
{
	init_kv();
	printf("Testing broadcast\n");
	broadcast_hello();
	printf("Client connect()\n");
	client_connect();
	printf("prot_handshake()\n");
	prot_handshake();
	printf("prot_run()\n");
	struct timespec req;
	req.tv_sec=0;req.tv_nsec=10000000LL;
	for(;;) {
		prot_process();
		nanosleep(&req,NULL);
	}
}
