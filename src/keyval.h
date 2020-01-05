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

int keyval_get( const char *path, char **status, 
                int *nparam, message_param **param );

int keyval_set( const char *path, char **status, 
                int nparam, message_param *param );

int keyval_add_p( const char *parent_path, keyval *child );

int keyval_add_k( keyval *parent, keyval *child );

keyval *keyval_create_ns  ( const char *name );
keyval *keyval_create_leaf( const char *name, 
                            const char *type, kv_get getter, kv_set setter );

void keyval_init();

#endif /* NETWORK_H_ */
