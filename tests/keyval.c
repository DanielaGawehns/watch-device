#include "keyval.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
keyval test;
keyval test_a;
keyval test_b;

void init_kv()
{
	keyval_init();
	test.type = "namespace";
	test.name = "test";
	test_a.type = "int";
	test_a.name = "a";
	test_b.type = "string";
	test_b.name = "b";
	assert( keyval_add_p( "", &test ) == 0 );
	assert( keyval_add_p( "test", &test_a ) == 0 );
	assert( keyval_add_p( "test", &test_b ) == 0 );
	
}

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
	printf("Testing get\n");
	test_get("");
	test_get(".");
	test_get("type");
	test_get(".type");
	test_get("test");
	test_get("test.");
	test_get("test.type");
	test_get("test.list");
}
