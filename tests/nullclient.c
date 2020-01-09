#include <assert.h>
#include <stdlib.h>

int client_connect( ) {
	assert( !"SHOULD NOT BE CALLED" );
	return 0;
}

void client_close( ) {
	assert( !"SHOULD NOT BE CALLED" );
}

int client_write( const void *data, size_t size ) {
	assert( !"SHOULD NOT BE CALLED" );
	return 0;
}

/**
 * Polls the number of bytes
 */
int client_available( ) {
	assert( !"SHOULD NOT BE CALLED" );
	return 0;
}

/**
 * Read data from the network connection
 * @param data The buffer to fill with data
 * @param size The number of bytes to read
 * @return 0
 */
int client_read( void *data, size_t size ) {
	assert( !"SHOULD NOT BE CALLED" );
	return 0;
}
