#ifndef __NETCORE_H__
#define __NETCORE_H__
void netcore_init();
int netcore_connect();
int netcore_send_increment( const char *sensor, double time,
                      int ndata, double *data ) ;
#endif
