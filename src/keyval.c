/*
 * keyval.c
 *
 *  Created on: Jan 4th, 2020
 *      Author: pbx
 */

/* enable strchrnul */
#define _GNU_SOURCE

#include "keyval.h"
#include <string.h>

keyval keyval_root;

/**
 * Selects a child node from a keyval by name.
 * @param kv     The keyval to query
 * @param name   The name to look for
 * @param namesz The length of the name string to consider. 
 * @warning name must be <= strlen( name )
 */
keyval *keyval_find_child( keyval *kv, const char *name, size_t namesz )
{
	keyval *v = kv->child;

	for ( v = kv->child; v != NULL; v = v->next ) {

		/* This comparison is safe as long as namesz <= strlen(name):
		 *   1. v->name is longer than namesz 
		 *       strncmp terminates successfully if there is a prefix match, 
		 *       but v->name[namesz] is not zero, as the string is longer. 
		 *   2. v->name is shorter than namesz and v->name != name
		 *       strncmp terminates with mismatch
		 *   2. v->name is shorter than namesz and there is a prefix match
		 *       strncmp terminates with mismatch
         *   4. name is shorter than namesz
		 *       unsafe but also prohibited! namesz must be <= strlen(name)
         */
		if ( strncmp( name, v->name, namesz ) == 0 && !v->name[namesz] )
			return v;

	}

	return NULL;
}

/**
 * Resolves a path within a keyval tree to a node.
 * If the node is not found, the rem_path output parameter will contain the
 * suffix of the path that could not be resolved and the last found parent 
 * will be returned.
 * Example: 
 *   keyval_resolve( foo, "a.b.nonexist.c.d.e", &rem_path )
 *       returns the node a.b
 *       rem_path is set to nonexist.c.d.e
 */
keyval *keyval_resolve( keyval *kv, const char *path, const char **rem_path )
{
	const char *sep;
	keyval *c;

	for ( ; ; ) {
		/* Find the next separator or the \0 */
		sep = strchrnul( path, '.' );

		/* Check if the first element in the path is a child */
		c = keyval_find_child( kv, path, sep - path );

		if ( !c ) {
			/* If not, return the parent and set rem_path */
			*rem_path = path;
			return kv;
		}

		/* Check if there are any more elements */
		if ( !*sep ) {
			/* If not, return the child and set rem_path to NULL */
			*rem_path = NULL;
			return c;
		}

		/* Update path, kv */
		kv = c;
		path = sep + 1;
	}

}

/**
 * Gets the value of a node
 * @param path    The node path to get
 * @param status  Status string output (or NULL, when out of memory),
 *                 to be freed by caller.
 * @param nparam  Number of values returned
 * @param param   Value list output, to be freed using prot_freeparams.
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_get( const char *path, char **status,
				int *nparam, message_param **param )
{
	int i, r;
	keyval *kv;
	const char *rem_path;

	kv = keyval_resolve( &keyval_root, path, &rem_path );

	*nparam = 0;

	if ( !rem_path ) {
		/* We found the node */
		if ( kv->nchild ) {
			/* Can't get something that is not a leaf */
			*status = strdup( "Tried to `get` a namespace" );
			return KV_EISDIR;
		} else if ( !kv->get ) {
			/* Get is not implemented for this node */
			*status = strdup( 
						"Tried to `get` something that is not implemented" );
			return KV_ENOSYS;
		}
		return kv->get( kv, status, nparam, param );
	}

	if ( strcmp( rem_path, "type" ) == 0 ) {

		*nparam = 1;

		*param = calloc( *nparam, sizeof( message_param ) );
		if ( !*param ) {
			goto nomem;
		}

		r = prot_set_param_s( (*param) + 0, kv->type );
		if ( r < 0 ) {
			goto nomem;
		}

		*status = strdup( "OK" );
		return 0;		
 
	} else if ( strcmp( rem_path, "list" ) == 0 ) {

		*nparam = kv->nchild;

		*param = calloc( *nparam, sizeof( message_param ) );
		if ( !*param ) {
			goto nomem;
		}

		kv = kv->child;
		for ( i = 0; i < *nparam; i++ ) {
			r = prot_set_param_s( (*param) + i, kv->name );
			if ( r < 0 ) {
				goto nomem;
			}
			kv = kv->next;
		}

		*status = strdup( "OK" );
		return 0;

	}

	*status = strdup( "Could not find node" );
	return KV_ENOENT;

nomem:
	*status = strdup( "Out of memory" );

	if ( !*param )
		prot_freeparam( *nparam, *param );

	*nparam = 0;
	*param = NULL;
	return KV_ENOMEM;
}

/**
 * Sets the value of a node
 * @param path    The node path to set
 * @param status  Status string output (or NULL, when out of memory),
 *                 to be freed by caller.
 * @param nparam  Number of values to set
 * @param param   Value list
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_set( const char *path, char **status, 
				int nparam, message_param *param )
{
	keyval *kv;
	const char *rem_path;

	kv = keyval_resolve( &keyval_root, path, &rem_path );

	if ( !rem_path ) {
		/* We found the node */
		if ( kv->child ) {
			/* Can't get something that is not a leaf */
			*status = strdup( "Tried to `get` a namespace" );
			return KV_EISDIR;
		} else if ( !kv->get ) {
			/* Get is not implemented for this node */
			*status = strdup( "Tried to `get` something that is not implemented" );
			return KV_ENOSYS;
		}
		return kv->set( kv, status, nparam, param );
	}

	*status = strdup( "Could not find node" );
	return KV_ENOENT;
}

/**
 * Add a child keyval to a node by path
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_add_p( const char *parent_path, keyval *child )
{
	const char *rem_path;
	keyval *parent;

	parent = keyval_resolve( &keyval_root, parent_path, &rem_path );

	if ( rem_path && *rem_path )
		return KV_ENOENT;

	return keyval_add_k( parent, child );
}

/**
 * Add a child keyval to a node by path
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_add_k( keyval *parent, keyval *child )
{
	parent->nchild++;
	child->next = parent->child;
	parent->child = child;
	return 0;
}

/**
 * Creates a namespace (non-leaf node)
 * @param name The name (not path) for the node to create
 */
keyval *keyval_create_ns( const char *name )
{
	keyval *kv = malloc( sizeof( keyval ) );
	if ( !kv )
		return NULL;
	memset( kv, 0, sizeof( keyval ) );
	kv->type = "namespace";
	kv->name = strdup( name );
	return kv;	
}

/**
 * Creates a leaf node with a set and get callback
 * @param name The name (not path) for the node to create
 */
keyval *keyval_create_leaf( const char *name, const char *type,
                            kv_get getter, kv_set setter, void *impl )
{
	keyval *kv = malloc( sizeof( keyval ) );
	if ( !kv )
		return NULL;
	memset( kv, 0, sizeof( keyval ) );
	kv->type = strdup( type );
	kv->name = strdup( name );
	kv->get  = getter;
	kv->set  = setter;
	kv->impl = impl;
	return kv;
}

void keyval_free( keyval *kv )
{
	free( kv->type );
	free( kv->name );
	free( kv );
}

/**
 * Creates a leaf node with a set and get callback and adds it to a parent node by label
 * @param name The name (not path) for the node to create
 */
keyval *keyval_create_add_k_leaf( keyval *parent, const char *name, const char *type,
                            kv_get getter, kv_set setter, void *impl  ) {
	int res;
	keyval *kv = keyval_create_leaf( name, type, getter, setter, impl );
	if ( !kv )
		return NULL;
	res = keyval_add_k( parent, kv );
	if ( res >= 0 )
		return kv;
	keyval_free( kv );
	return NULL;
}

/**
 * Initializes the key value abstraction layer
 */
void keyval_init()
{
	keyval_root.type = "root";
	keyval_root.name = "";
}
