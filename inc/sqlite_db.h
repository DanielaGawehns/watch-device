#if !defined(_SQLITE_DB_H)
#define _SQLITE_DB_H

#include "sensorbasicui.h"
#include "data.h"//used for sensor support
#include <sqlite3.h> //used for database


//------------------------------ Database constants, can be made modular but there was no need yet
 /* Buffer size, used in functions */
#define BUFLEN 800
#define MAX_SIZE_DATA_PATH 800
#define dbDataCols 6
static const unsigned char tableName[] = {"DataTable"};
//----------------------------------

//struct for sensordata
struct __attribute__((__packed__)) data {
	unsigned long long epoch; //epoch in milliseconds
	float values[dbDataCols];
};
typedef struct data data; //refer to struct data with type data

/**
 * @brief Gets the full path to a write/readable file in the datafolder (this does not check if it exists)
 * @param WriteFile: name of the file to get the full path from
 */
data *database_create_data_entry(unsigned long long epoch);


/**
 * @brief Gets the full path to a write/readable file in the datafolder (this does not check if it exists)
 * @param WriteFile: name of the file to get the full path from
 * @return pointer to char array containing filepath
 */
char * database_get_file_path(char * writeFile);


/**
 * @brief open the database to allow for reading and storing of data
 * @return succes state
 */
int
database_open_database();

/**
 * @brief close the database
 * @return succes state
 */
int
database_close_database();


/**
 * @brief writes sensor data to the database file in the datafolder of the watch
 * @param count amount of fields in the data
 * @param valArr pointer to the data from the sensor
 * @param sensorType name of the sensor that wants to log data
 */
int
database_insert_data(int count, sensor_event_s *ev,  sensor_type_e sensorType);



/**
 * @brief puts data from database between time1 and time2 and from sensor sensor_name in passed buffer
 * @brief The buffer is filled with struct data
 * @param sensor_name sensor of which to get the data, name is in string form (e.g. "ACCELEROMETER")
 * @time1 1 of the between dates, supplied as milliseconds since epoch
 * @time2 2 of the between dates, supplied as milliseconds since epoch
 * @*ndata pointer to buffer that is to be filled
 * @buffersize size of the supplied buffer in bytes
 * @*writtenRows the amount of rows that were written to the buffer
 * @return succes state
 */

//2020-02-02T02:11:33.930
int
database_get_data(const char * sensor_name, unsigned long long time1, unsigned long long time2, char *ndata, int buffersize, int *writtenRows);


/**
 * @brief open a table within the database
 * @return succes state
 */
int
database_open_table();

#endif
