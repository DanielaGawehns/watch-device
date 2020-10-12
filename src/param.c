/**
 * @file param.c
 * @date Jan 10, 2020
 * @brief parameters
 */

#include "protocol.h"
#include "keyval.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define _BSD_SOURCE
#include <endian.h>

/**
 * Encode a long long to a memory buffer
 */
void prot_encode_long( void *output, long long value ) {
	*(uint64_t *)output = htobe64( value );
}

/**
 * Decode a long long from a memory buffer
 */
long long prot_decode_long( const void *output ) {
	return be64toh(*(uint64_t *)output);
}

/**
 * Encode an int to a memory buffer
 */
void prot_encode_int( void *output, int value ) {
	*(uint32_t *)output = htobe32( value );
}

/**
 * Decode an int from a memory buffer
 */
int prot_decode_int( const void *output ) {
	return be32toh(*(uint32_t *)output);
}

/**
 * Encode a double to a memory buffer
 */
void prot_encode_double( void *output, double value ) {
	uint64_t bytes = *(uint64_t *)&value;
	*(uint64_t *)output = htobe64( bytes );
}

/**
 * Decode a double from a memory buffer
 */
double prot_decode_double( const void *output ) {
	double value;
	*(uint64_t *)&value = be64toh( *(uint64_t *)output );
	return value;
}

/**
 * Sets a param to a long long value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_l( message_param *param, long long value )
{

	assert( param != NULL );

	/* Set length */
	param->length = sizeof value;

	/* Allocate buffer and catch OOM*/
	param->data   = malloc( param->length );
	if ( !param->data )
		return -1;

	prot_encode_long( param->data, value );

	return 0;

}

/**
 * Sets a param to an integer value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_i( message_param *param, int value )
{

	assert( param != NULL );

	/* Set length */
	param->length = sizeof value;

	/* Allocate buffer and catch OOM*/
	param->data   = malloc( param->length );
	if ( !param->data )
		return -1;

	prot_encode_int( param->data, value );

	return 0;

}

/**
 * Sets a param to a double value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_d( message_param *param, double value )
{

	assert( param != NULL );

	/* Set length */
	param->length = sizeof value;

	/* Allocate buffer and catch OOM*/
	param->data   = malloc( param->length );
	if ( !param->data )
		return -1;

	prot_encode_double( param->data, value );

	return 0;

}

/**
 * Sets a param to a string value.
 * This allocates a buffer so that the params can always
 * be freed, regardless of source
 */
int prot_set_param_s( message_param *param, const char *value )
{

	assert( param != NULL );

	/* Set length */
	param->length = strlen( value );

	/* Copy string and catch OOM*/
	param->data   = strdup( value );
	if ( !param->data )
		return -1;

	return 0;

}


/**
 * Frees a message_param struct
 */
void prot_freeparam( int nparam, message_param *param ){
	int i;
	/* Iterate over the parameters */
	for ( i = 0; i < nparam; i++ ) {
		/* Check if the data pointer is set */
		if ( param[i].data ) {
			/* If so, free the data buffer */
			free( param[i].data );
		}
	}
	free( param );
}

int prot_create_param_list( char **status, int *nparam, message_param **param ) {
	*param = calloc( sizeof(message_param), *nparam );
	if ( !*param ) {
		*nparam = 0;
		*status = strdup( "Out of memory" );
		return -1;
	}
	return 0;
}

/**
 * @brief Creates a parameter list with one string parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1s( char **status, 
                          int *nparam, message_param **param, 
                          const char *value )
{
	int r;

	/* Set the list size */
	*nparam = 1;

	/* Create the list */
	r = prot_create_param_list( status, nparam, param );
	if ( r < 0 )
		return r;

	/* Set the parameter */
	r = prot_set_param_s( *param, value );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	*status = strdup( "OK" );
	return 0;
	
}

/**
 * @brief Creates a parameter list with one integer parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1i( char **status, 
                          int *nparam, message_param **param, 
                          int value )
{
	int r;

	/* Set the list size */
	*nparam = 1;

	/* Create the list */
	r = prot_create_param_list( status, nparam, param );
	if ( r < 0 )
		return r;

	/* Set the parameter */
	r = prot_set_param_i( *param, value );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	*status = strdup( "OK" );
	return 0;
	
}

/**
 * @brief Creates a parameter list with one long long parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1l( char **status, 
						  int *nparam, message_param **param, 
						  long long value )
{
	int r;

	/* Set the list size */
	*nparam = 1;

	/* Create the list */
	r = prot_create_param_list( status, nparam, param );
	if ( r < 0 )
		return r;

	/* Set the parameter */
	r = prot_set_param_l( *param, value );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	*status = strdup( "OK" );
	return 0;
	
}

/**
 * @brief Creates a parameter list with one double parameter and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_1d( char **status, 
                          int *nparam, message_param **param, 
                          double value )
{
	int r;

	/* Set the list size */
	*nparam = 1;

	/* Create the list */
	r = prot_create_param_list( status, nparam, param );
	if ( r < 0 )
		return r;

	/* Set the parameter */
	r = prot_set_param_d( *param, value );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	*status = strdup( "OK" );
	return 0;
	
}

/**
 * @brief Creates a parameter list with two double parameters and returns.
 * If this is succesful, the status output will be set to "OK",
 * otherwise, the status output will be set to contain a friendly error
 * message.
 * This function can be used as a convenient chainreturn on functions.
 * @param status  Friendly status message output
 * @param nparam  Parameter count output
 * @param param   Parameter list pointer output
 * @param value   The value to copy into the parameter list.
 * @return 0 when successful. or -1 if not.
 */
int prot_create_param_2d( char **status,
                          int *nparam, message_param **param,
                          double val1, double val2 )
{
	int r;

	/* Set the list size */
	*nparam = 2;

	/* Create the list */
	r = prot_create_param_list( status, nparam, param );
	if ( r < 0 )
		return r;

	/* Set the parameter */
	r = prot_set_param_d( *param, val1 );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	/* Set the parameter */
	r = prot_set_param_d( (*param) + 1, val2 );
	if ( r < 0 ) {
		/* Clean up in the case of an error */
		/* Errors on this function result in an empty parameter list */
		prot_freeparam( *nparam, *param );
		*nparam = 0;
		*param = NULL;
		*status = strdup( "Out of memory" );
		return r;
	}

	*status = strdup( "OK" );
	return 0;

}

