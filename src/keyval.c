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

keyval *keyval_find_child( keyval *kv, const char *name, size_t namesz )
{
	keyval *v = kv->child;
	for ( v = kv->child; v != NULL; v = v->next ) {
		if ( strncmp( name, v->name, namesz ) == 0 && !v->name[namesz] )
			return v;
	}

	return NULL;
}

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

int keyval_get( const char *path, char **status, int *nparam, message_param **param )
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
			*status = "Tried to `get` a namespace";
			return KV_EISDIR;
		} else if ( !kv->get ) {
			/* Get is not implemented for this node */
			*status = "Tried to `get` something that is not implemented";
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

		*status = "OK";
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

		*status = "OK";
		return 0;
	}

	*status = "Could not find node";
	return KV_ENOENT;

nomem:
	*status = "Out of memory";
	if ( !*param )
		prot_freeparam( *nparam, *param );
	*nparam = 0;
	*param = NULL;
	return KV_ENOMEM;
}

int keyval_set( const char *path, char **status, int nparam, message_param *param )
{
	keyval *kv;
	const char *rem_path;

	kv = keyval_resolve( &keyval_root, path, &rem_path );

	if ( !rem_path ) {
		/* We found the node */
		if ( kv->child ) {
			/* Can't get something that is not a leaf */
			*status = "Tried to `get` a namespace";
			return KV_EISDIR;
		} else if ( !kv->get ) {
			/* Get is not implemented for this node */
			*status = "Tried to `get` something that is not implemented";
			return KV_ENOSYS;
		}
		return kv->set( kv, status, nparam, param );
	}

	*status = "Could not find node";
	return KV_ENOENT;
}

int keyval_add_p( const char *parent_path, keyval *child )
{
	const char *rem_path;
	keyval *parent;

	parent = keyval_resolve( &keyval_root, parent_path, &rem_path );

	if ( rem_path && *rem_path )
		return KV_ENOENT;

	return keyval_add_k( parent, child );
}

int keyval_add_k( keyval *parent, keyval *child )
{
	parent->nchild++;
	child->next = parent->child;
	parent->child = child;
	return 0;
}

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

keyval *keyval_create_leaf( const char *name, const char *type,
                            kv_get getter, kv_set setter )
{
	keyval *kv = malloc( sizeof( keyval ) );
	if ( !kv )
		return NULL;
	memset( kv, 0, sizeof( keyval ) );
	kv->type = strdup( type );
	kv->name = strdup( name );
	kv->get  = getter;
	kv->set  = setter;
	return kv;
}


void keyval_init()
{
	keyval_root.type = "root";
	keyval_root.name = "";
}
