/*
 * protocol.h
 *
 *  Created on: Dec 6, 2019
 *      Author: pbx
 */

#ifndef PROT_CMDS_H_
#define PROT_CMDS_H_

#include "protocol.h"

int prot_send_reply( int seq, int status, const char *msg, 
                      int nparam, message_param *param );

/**
 * Called by the protocol handler when a MESSAGE_SENSOR_INTERVAL comes in
 */
void cmd_sensor_interval( const char *sensor_name, double interval );

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_get_values( int seq, const char *path );

/**
 * Called by the protocol handler when a MESSAGE_SET_VALUES comes in
 */
void cmd_set_values( int seq, const char *path, int nparam, message_param *param );

/**
 * Called by the protocol handler when a MESSAGE_LIVE_INTERVAL comes in.
 */
void cmd_live_interval  ( double interval );

#endif
