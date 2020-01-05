/*
 * keyval.h
 *
 *  Created on: Jan 4th, 2020
 *      Author: pbx
 */

#ifndef KEYVAL_H_
#define KEYVAL_H_

#include <stdlib.h>
#include "protocol.h"

#define KV_ENOENT		(-1)
#define KV_EISDIR		(-2)
#define KV_ENOSYS		(-3)
#define KV_ENOMEM    	(-4)

typedef struct keyval_s keyval;

typedef int (*kv_get) ( keyval *kv, char **status, 
                      int *nparam, message_param **param );

typedef int (*kv_set) ( keyval *kv, char **status, 
                      int  nparam, message_param *param );

struct keyval_s {
	int         nchild;
	const char *type;	
	const char *name;
	keyval     *next;
	keyval     *child;
	kv_get      get;
	kv_set      set;
	void       *impl;
};

extern keyval keyval_root;

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
                int *nparam, message_param **param );

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
                int nparam, message_param *param );

/**
 * Add a child keyval to a node by path
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_add_p( const char *parent_path, keyval *child );

/**
 * Add a child keyval to a node by path
 * @return If successful: 0, KV_E* constants (<0) when failed
 */
int keyval_add_k( keyval *parent, keyval *child );

/**
 * Creates a namespace (non-leaf node)
 * @param name The name (not path) for the node to create
 */
keyval *keyval_create_ns  ( const char *name );

/**
 * Creates a leaf node with a set and get callback
 * @param name The name (not path) for the node to create
 */
keyval *keyval_create_leaf( const char *name, 
                            const char *type, kv_get getter, kv_set setter );

void keyval_init();

#endif /* NETWORK_H_ */
