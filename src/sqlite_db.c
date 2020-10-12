/**
 * @file sqlite_db.c
 * @date Jan 10, 2020
 * @brief Implementation of the database on the watch
 */
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlog.h>
#include <stdint.h>
#define TRUE (1)
#define FALSE (0)
#include <sqlite3.h> //used for database
#include "protocol.h"
#include "sqlite_db.h"
#define LOG_TAG "sensorbasicui"

sqlite3 *db; /* Database handle */
sqlite3_stmt *db_insert_stmt;
sqlite3_stmt *db_playback_stmt;

typedef struct {
	int sensor;
	int timestamp;
	int ndata;
	int data[8];
} db_row_indices;

db_row_indices db_insert_indices;
char dbfile_path[MAX_SIZE_DATA_PATH];

int db_initialized = FALSE;

/**
 * @brief Sets up the database path.
 * @param filename The name of the file to have the database use.
 */
void database_setup_path( const char *filename ) {
	char * data_path = database_get_data_path(); //get pointer to data path

	assert( data_path != NULL );

	//TODO: Do we need the separator here?
	snprintf(dbfile_path, sizeof dbfile_path, "%s%s", data_path, filename);
	free(data_path);
	
}

void database_generate_row_indices( sqlite3_stmt *stmt, db_row_indices *idxs )
{
	int i;
	char cn[10];
	
	assert( idxs != NULL );

	idxs->sensor    = sqlite3_bind_parameter_index( stmt, "$sensor" );
	idxs->timestamp = sqlite3_bind_parameter_index( stmt, "$timestamp" );
	idxs->ndata     = sqlite3_bind_parameter_index( stmt, "$ndata" );

	for ( i = 0; i < DB_MAX_NDATA; i++ ) {

		snprintf( cn, sizeof cn, "$data%i", i );

		idxs->data[i] = sqlite3_bind_parameter_index( stmt, cn );
		assert( idxs->data[i] != 0 );
	}
	assert( idxs->sensor != 0 );
	assert( idxs->timestamp != 0 );
	assert( idxs->ndata != 0 );

	//TODO: Validate indices

}

int database_prepare_statements ( void )
{
	int status;
	const char *insert_sql = 
		"INSERT INTO wsensor_data ("
		" sensor, timestamp, ndata,"
		" data0, data1, data2, data3,"
		" data4, data5, data6, data7 " 
		") VALUES ("
		" $sensor, $timestamp, $ndata,"
		" $data0, $data1, $data2, $data3,"
		" $data4, $data5, $data6, $data7"
		");";

	const char *playback_sql =
		"SELECT "
		" (SELECT COUNT(*) FROM wsensor_data WHERE timestamp BETWEEN ?1 AND ?2), *"
		" FROM wsensor_data "
		"WHERE timestamp BETWEEN ?1 AND ?2;";

	assert( db != NULL );

	status = sqlite3_prepare_v2(
		/* db */     db,
		/* sql */    insert_sql,
		/* nByte */  strlen( insert_sql ),
		/* ppStmt */ &db_insert_stmt,
		/* tail */   NULL );
	if ( status != SQLITE_OK )
		goto error;
	assert( db_insert_stmt != NULL );

	database_generate_row_indices( db_insert_stmt, &db_insert_indices ); 

	status = sqlite3_prepare_v2(
		/* db */     db,
		/* sql */    playback_sql,
		/* nByte */  strlen( playback_sql ),
		/* ppStmt */ &db_playback_stmt,
		/* tail */   NULL );
	if ( status != SQLITE_OK )
		goto error;
	assert( db_playback_stmt != NULL );

	return 0;
error:
	database_fatal_error( 
		"Could not create statement: %i %s", 
		status,
		sqlite3_errmsg(db) );
	return -1;
		
	
}

/**
 * @brief open the database to allow for reading and storing of data
 * @return succes state
 */
int database_open_database( void )
{
	int status;

	/* Do not re-initialize the database */
	if ( db_initialized )
		return 0;

	database_setup_path("test.db"); //TODO: Better name

	/* Open the SQLite3 database */
	status = sqlite3_open_v2( 
		/* path */       dbfile_path, 
		/* db pointer */ &db, 
		/* flags */      SQLITE_OPEN_FULLMUTEX | 
	                         SQLITE_OPEN_READWRITE | 
	                         SQLITE_OPEN_CREATE, 
		/* vfs */        NULL );

	/* Check if we were successful */
	if ( status != SQLITE_OK ) {
		database_fatal_error( 
			"Could not open database %s, SQLite3 error was %i", 
			dbfile_path,
			status );
		return -1;
	}
	
	assert( db != NULL );

	database_init_schema();

	database_prepare_statements();

	db_initialized = TRUE;

	return 0;
}

/**
 * @brief close the database
 * @return succes state
 */
int database_close_database( void )
{

	/* Clean up prepared statements */
	if ( db_insert_stmt )
		sqlite3_finalize( db_insert_stmt );

	/* Tell SQLite3 to close the database */
	sqlite3_close( db );

	/* Make sure we do not assume the DB is open anymore */
	db_initialized = FALSE;

	/* Also clean up the DB pointer */
	db = NULL;

	return 0;
}

int database_init_schema( void ) {

	int status;
	char *err_msg;
	const char *pragma_sync_stmt = "PRAGMA synchronous = FULL;";

	const char *init_tbl_stmt = 
		"CREATE TABLE IF NOT EXISTS wsensor_data ("
		"	id        INTEGER     NOT NULL PRIMARY KEY,"
		"	sensor	  VARCHAR(32) NOT NULL,"
		"	timestamp UNSIGNED BIG INT,"
		"	ndata     INTEGER,"
		"	data0     REAL,"
		"	data1     REAL,"
		"	data2     REAL,"
		"	data3     REAL,"
		"	data4     REAL,"
		"	data5     REAL,"
		"	data6     REAL,"
		"	data7     REAL"
		");";

	/* Assert that we have a database pointer */	
	assert( db != NULL );

	/* Execute the schema statement */
	status = sqlite3_exec(
		/* db */       db, 
		/* sql */      pragma_sync_stmt,
		/* callback */ NULL,
		/* arg */      NULL,
		/* errmsg */   &err_msg );

	/* Report any errors */
	if ( status != SQLITE_OK ) {

		database_fatal_error(
			"Could not execute pragma: %i, %s",
			status,
			err_msg );

		status = -1;

	} else
		status = 0;

	/* Execute the schema statement */
	status = sqlite3_exec(
		/* db */       db,
		/* sql */      init_tbl_stmt,
		/* callback */ NULL,
		/* arg */      NULL,
		/* errmsg */   &err_msg );

	/* Report any errors */
	if ( status != SQLITE_OK ) {

		database_fatal_error(	
			"Could not execute schema: %i, %s", 
			status,
			err_msg );

		status = -1;

	} else
		status = 0;

	/* Clean up the error message memory */
	if ( err_msg )
		free( err_msg );

	return status;

}

/**
 * @brief writes sensor data to the database file in the datafolder of the watch
 * @param count amount of fields in the data
 * @param valArr pointer to the data from the sensor
 * @param sensorType name of the sensor that wants to log data
 */
int database_record_data( 
	const char *sensor, 
	long long time, 
	int ndata, double *data )
{
	int status, i;

	assert( db != NULL );
	assert( db_insert_stmt != NULL );
	assert( sensor != NULL );
	assert( data != NULL );
	assert( ndata <= DB_MAX_NDATA );
	
	if ( !db_initialized ) {
		database_data_error( "Database not initialized!" );
		return -1;
	}
	
	/* Bind the parameters */
	status = sqlite3_bind_text( 
		/* stmt */   db_insert_stmt, 
		/* index */  db_insert_indices.sensor,
		/* value */  sensor,
		/* nBytes */ strlen( sensor ),
		/* dtor */   SQLITE_TRANSIENT );

	if ( status != SQLITE_OK )
		goto bind_error;
	
	status = sqlite3_bind_int64( 
		/* stmt */  db_insert_stmt, 
		/* index */ db_insert_indices.timestamp,
		/* value */ time );

	if ( status != SQLITE_OK )
		goto bind_error;
	
	status = sqlite3_bind_int( 
		/* stmt */  db_insert_stmt, 
		/* index */ db_insert_indices.ndata,
		/* value */ ndata );

	if ( status != SQLITE_OK )
		goto bind_error;

	for ( i = 0; i < ndata; i++ ) {
	
		status = sqlite3_bind_double( 
			/* stmt */  db_insert_stmt, 
			/* index */ db_insert_indices.data[i],
			/* value */ data[i] );

		if ( status != SQLITE_OK )
			goto bind_error;
	}

	/* Execute the statement */
	status = sqlite3_step( db_insert_stmt );

	/* Check if this succeded */
	if ( status != SQLITE_DONE )
		goto step_error;

	status = 0;
	
cleanup:
	sqlite3_reset( db_insert_stmt );
	sqlite3_clear_bindings( db_insert_stmt );
	//TODO: Check status of these?
	return status;

bind_error:
	database_data_error( "Could not bind parameters: %i", status );
	status = -1;
	goto cleanup;

step_error:
	database_data_error( "Could not run statement: %i", status );
	status = -1;
	goto cleanup;

}

int database_playback_dorow()
{
	int i;
	long long timestamp;
	int ndata = 0;
	const char *sensor;
	double data[ DB_MAX_NDATA ];

	/* Get the columns */
	sensor = sqlite3_column_text( db_playback_stmt, 2 );
	
	if ( sensor == NULL )
		return -1;

	timestamp = sqlite3_column_double( db_playback_stmt, 3 );

	ndata = sqlite3_column_int( db_playback_stmt, 4 );

	if ( ndata > DB_MAX_NDATA ) {

		database_data_error( 
			"Too many data entries in row: %i", 
			ndata );

		return -1;
	}

	for ( i = 0; i < ndata; i++ ) {

		data[i] = sqlite3_column_double( db_playback_stmt, i + 5 );

	}	

	/* Send the playback packet */

	dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] sending playback row ts=%lld ndata=%d { %f, %f, %f }", __FILE__, __LINE__ , timestamp, ndata, data[0], data[1], data[2]);
	return prot_send_playback( sensor, timestamp, ndata, data );
}

// seq: the sequence of the message in the connection (REVIEW)
//
// if statusmsg is not NULL, an error is sent.  this function takes ownership
// over statusmsg, and will free it.
//
// rowcount is the amount of rows that will be sent to the host.
void send_playback_reply(int seq, int status, char *statusmsg, int64_t rowcount) {
	int nparam = 0;
	message_param *param = NULL;

	// if statusmsg is not null we want to send an error.
	if (statusmsg == NULL) {
		status = prot_create_param_1l( 
			&statusmsg, 
			&nparam, 
			&param, 
			rowcount );

		if (statusmsg == NULL) {
			statusmsg = strdup("NULL STATUS MESSAGE!");
		}
	}

	prot_send_reply( seq, status, statusmsg, nparam, param );
	
	if ( param )
		prot_freeparam( nparam, param );

	if ( statusmsg )
		free( statusmsg );
}

void cmd_get_playback( int seq, long long time_start, long long time_end )
{
	bool first = true;
	char *statusmsg = NULL;
	int nparam, status = 0;
	message_param *param = NULL;

	/* Bind the parameters */
	
	status = sqlite3_bind_int64( 
		/* stmt */  db_playback_stmt, 
		/* index */ 1,
		/* value */ time_start );
	if ( status != SQLITE_OK )
		goto bind_error;
	
	status = sqlite3_bind_int64( 
		/* stmt */  db_playback_stmt, 
		/* index */ 2,
		/* value */ time_end );
	if ( status != SQLITE_OK )
		goto bind_error;

	for ( ;; ) {
		status = sqlite3_step( db_playback_stmt );

		if ( status == SQLITE_DONE ) {
			/* This was the last result */
			status = 0;
			break;
		} else if ( status != SQLITE_ROW ) {
			/* Something went wrong */
			status = -1; //TODO: Lookup protocol error codes
			statusmsg = strdup( "Error during query!" );
			break;
		}

		if (first) {
			int64_t rowcount = sqlite3_column_int64( db_playback_stmt, 0 );
			dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] sending rowcount of %lld", __FILE__, __LINE__ , rowcount);
			send_playback_reply(seq, 0, NULL, rowcount);
			first = false;
		}

		/* We've got a valid row out of the database, play it back */
		database_playback_dorow();
	}

send_error_reply:
	if (first) {
		// this will also be hit when the amount of rows in the given datarange
		// is zero.
		// status will be 0, statusmsg will be NULL.
		// This means that no error will be sent.
		// We fix the rowcount to 0, this should be ignored by the host if
		// status is not equal to 0.
		send_playback_reply(seq, status, statusmsg, 0);
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] sent error (status: %d, statusmsg: %s)", __FILE__, __LINE__ , status, statusmsg);
	} else if (status != 0) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] was going to send an error, but can't because first == false (status: %d, statusmsg: %s)", __FILE__, __LINE__ , status, statusmsg);
	}
	
cleanup:
	sqlite3_reset( db_playback_stmt );
	sqlite3_clear_bindings( db_playback_stmt );
	//TODO: Check status of these?
	return;

bind_error:
	status = -1;
	statusmsg = strdup( "Could not bind parameters!" );
	goto send_error_reply;

}

