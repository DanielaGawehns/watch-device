/**
 * @file sqlite_db.h
 * @date Jan 10, 2020
 * @brief Implementation of the database on the watch
 */

#if !defined(_SQLITE_DB_H)
#define _SQLITE_DB_H

#include <sqlite3.h> //used for database


//------------------------------ Database constants, can be made modular but there was no need yet
 /* Buffer size, used in functions */
#define BUFLEN 800
#define MAX_SIZE_DATA_PATH 800
#define DB_MAX_NDATA 6
//------------------
int database_open_database( void );

int database_init_schema( void );

int database_record_data( 
	const char *sensor, 
	long long time, 
	int ndata, double *data );

char *database_get_data_path( void );

void database_fatal_error( const char *fmt, ... );

void database_data_error( const char *fmt, ... );

#endif
