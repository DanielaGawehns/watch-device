

#include "protocol.h"
#include "keyval.h"
#include <string.h>
#include <stdlib.h>

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

