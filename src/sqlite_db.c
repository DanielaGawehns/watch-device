

#include "sensorbasicui.h"
#include "data.h"//used for sensor support
#include <sqlite3.h> //used for database

//------------------------------ Temporary database constants
 /* Buffer size, used in functions */
#define BUFLEN 800
#define MAX_SIZE_DATA_PATH 800
 /* AES key length */
static const unsigned char tableName[] = {"DataTable"};
const int dbDataCols = 6;
sqlite3 *db; /* Database handle */
bool openedDatabase = false; //opened database
bool openedTable = false; //made sure data table exists
//----------------------------------

//struct for sensordata
struct __attribute__((__packed__)) data {
	unsigned long long epoch; //epoch in milliseconds
	float values[dbDataCols];
};
typedef struct data data; //refer to struct data with type data

data *createDataEntry(unsigned long long epoch) {
	data *d = malloc(sizeof(struct data));
	d->epoch = epoch;
	memset(d->values, 0, sizeof(d->values));
	return d;
}

/**
 * @brief Gets the full path to a write/readable file in the datafolder (this does not check if it exists)
 * @param WriteFile: name of the file to get the full path from
 * @return pointer to char array containing filepath
 */
char * get_filepath(char * writeFile){
	char * finalPath = (char*) malloc(MAX_SIZE_DATA_PATH * sizeof(char)); //[MAX_SIZE_DATA_PATH] = {0,}; //max path size is 800, initialize all chars to 0
	char * dataPath = app_get_data_path(); //get pointer to data path
	if(sizeof(dataPath) > 0){ //if datapath exists
		snprintf(finalPath, MAX_SIZE_DATA_PATH, "%s%s", dataPath, writeFile);
		free(dataPath);
	}
	return finalPath;
}




/**
 * @brief open the database to allow for reading and storing of data
 * @return succes state
 */
int
OpenDatabase(){
	int ret = 0;
	if(!openedDatabase){ //if database is not yet opened TODO: keep database open? Or close after each use
		sqlite3_shutdown(); //shutdown the database TODO: is this neccesary?
		char * dbPath = get_filepath("test.db"); //get filepath
		//ret = sqlite3_open_v2(dbPath, &db, SQLITE_OPEN_FULLMUTEX, NULL); //open database (serialized mode - fullmutex) TODO: is this necessary (callback ensures only one acces to database per time)
		ret = sqlite3_open(dbPath, &db); //open database (serialized mode - fullmutex)
		if(ret != SQLITE_OK){
			dlog_print(DLOG_ERROR, LOG_TAG, "ERROR WHILE OPENING DATABASE, ERROR CODE: %i", ret); //print error
			return ret;
		}

		dlog_print(DLOG_INFO, LOG_TAG, "OPENED DATABASE %s SUCCESFULLY", dbPath); //print error
		openedDatabase = true;
	}else{
		dlog_print(DLOG_INFO, LOG_TAG, "DATABASE ALREADY OPEN"); //if database is already open
	}
	return ret;
}

/**
 * @brief close the database
 * @return succes state
 */
int
CloseDatabase(){
	sqlite3_close(db);
	openedDatabase = false;
	openedTable = false;
	dlog_print(DLOG_INFO, LOG_TAG, "CLOSED DATABASE SUCCESFULLY"); //print error
	return 0;
}


/**
 * @brief writes sensor data to the database file in the datafolder of the watch
 * @param count amount of fields in the data
 * @param valArr pointer to the data from the sensor
 * @param sensorType name of the sensor that wants to log data
 */
int
InsertDataInDatabase(int count, sensor_event_s *ev,  sensor_type_e sensorType){
	char dataBuf[2000]; //create buffer for storing the sensor data
	int ret = SQLITE_OK; //return value

	struct tm * timeInfo;
	struct timeval timeValue;
	gettimeofday(&timeValue, NULL);
	timeInfo = localtime(&timeValue.tv_sec);

	unsigned long long cur = (unsigned long long)(timeValue.tv_sec) * 1000 + (unsigned long long)(timeValue.tv_usec) / 1000;

	snprintf(dataBuf, sizeof(dataBuf), "\'%s\'",sensor_strings[sensorType]); //put sensortype, into databuffer

	//strftime(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",\'%Y-%m-%dT%H:%M:%S", timeInfo); //put day, time (h:m:s) into databuffer

	snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",%llu", cur); //millisec
	//snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ".%i\'", (int) (timeValue.tv_usec / 1000)); //millisec

	for(int i = 0 ; i < count; i++){ //TODO: make sure amount of columns is not exceeded?
		snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",%f", ev->values[i]); //write all sensordata into buffer
	}
	for(int i = count; i < dbDataCols; i++){ //append ',' until all cols are filled	TODO: also edit when making amount of cols modular
		snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",0" );
	}

	//Insert prepared datastring into the database
	if(openedTable){ //if table has not yet been opened (not sure whether it exists or not
		char *  statementString = sqlite3_mprintf("INSERT INTO %Q (sensor_name, timestamp, data1, data2, data3, data4, data5, data6) VALUES (%s)", tableName, dataBuf); //insert databuf into table
		//char *  statementString = sqlite3_mprintf("INSERT INTO %Q (sensor_name, data1, data2, data3, data4, data5) VALUES (%s)", tableName, dataBuf); //insert databuf into table
		ret = sqlite3_exec(db, statementString, NULL, NULL, NULL);
		if(ret == SQLITE_OK){
			dlog_print(DLOG_INFO, LOG_TAG, "SUCCESFULLY EXECUTED: %s", statementString);
		}else{
			dlog_print(DLOG_ERROR, LOG_TAG, "COULD NOT INSERT SENSORDATA IN TABLE %s, ERROR CODE: %i, QUERY: %s ", tableName, ret, statementString); //print info
		}
		sqlite3_free(statementString);
	}else{
		dlog_print(DLOG_ERROR, LOG_TAG, "TABLE %s WAS NOT OPENED, COULD NOT INSERT SENSORDATA", tableName); //print info
	}
	return ret;
}

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
GetDataFromDatabase(const char * sensor_name, unsigned long long time1, unsigned long long time2, char *ndata, int buffersize, int *writtenRows){
	int writtenEntries = 0;
	int ret = SQLITE_OK; //return value
	int rowret = SQLITE_OK; //return value for retrieving data from database
	//Insert prepared datastring into the database
	if(openedTable){ //if table has not yet been opened (not sure whether it exists or not
		sqlite3_stmt* stmt;
		char * statementString = sqlite3_mprintf("SELECT * FROM %Q WHERE sensor_name LIKE %Q AND timestamp BETWEEN %llu AND %llu", tableName, sensor_name, time1, time2); //insert databuf into table
		ret = sqlite3_prepare_v2(db, statementString, -1, &stmt, NULL);
		if(ret != SQLITE_OK){
			dlog_print(DLOG_ERROR, LOG_TAG, "Could not prepare SQL statement");
		}
		while(ret == SQLITE_OK && (rowret = sqlite3_step(stmt)) != SQLITE_DONE){ //TODO: safe like this?
			data* entry = NULL; //new entry
			if(rowret != SQLITE_ROW){
				dlog_print(DLOG_ERROR, LOG_TAG, "Row output not available");
				continue;
			}
			else {
				entry = createDataEntry(sqlite3_column_int64(stmt, 1));
				for(int i = 2; i < dbDataCols; i++){	//loop over columns with data
					entry->values[i-2] = sqlite3_column_double(stmt, i);
				}
				if(entry != NULL){
					if ((writtenEntries+1)*sizeof(data) > buffersize){
						ret = SQLITE_NOMEM;
						dlog_print(DLOG_ERROR, LOG_TAG, "Buffer is full, data retrieval incomplete"); //print info
					}
					else {
						memcpy(ndata, entry, sizeof(data));
						writtenEntries++;
						/*data test;
						memcpy(&test, ndata, sizeof(data));
						dlog_print(DLOG_DEBUG, LOG_TAG, "Test values: Date: %llu  Value1: %f  Value2: %f  Value3: %f Value4: %f Value5: %f Value6: %f", test.epoch, test.values[0], test.values[1], test.values[2], test.values[3], test.values[4], test.values[5]);
						*/
						ndata += sizeof(data);
					}
				}
				else{
					dlog_print(DLOG_DEBUG, LOG_TAG, "No data was found in row");
				}
			}
			free(entry);
			entry = NULL;
		}
		sqlite3_finalize(stmt);
		*writtenRows = writtenEntries;
		if(ret == SQLITE_OK){
			dlog_print(DLOG_INFO, LOG_TAG, "SUCCESFULLY EXECUTED: %s", statementString);
		}else{
			dlog_print(DLOG_ERROR, LOG_TAG, "SENSORDATA IN TABLE %s, ERROR CODE: %i, QUERY: %s ", tableName, ret, statementString); //print info
		}
		sqlite3_free(statementString);
	}else{
		dlog_print(DLOG_ERROR, LOG_TAG, "TABLE %s WAS NOT OPENED, COULD NOT INSERT SENSORDATA", tableName); //print info
	}
	return ret; //TODO
}

/**
 * @brief open a table within the database
 * @return succes state
 */
int
OpenTable(){
	char * statementString; // = sqlite3_mprintf("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='{%Q}'", tableName); //create statement using opened tablename : if table exists, count >0
	int ret = SQLITE_OK; //return value
	if(!openedTable || true){ //if table has not yet been opened (not sure whether it exists or not
		statementString = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS %s(sensor_name TEXT, timestamp UNSIGNED BIG INT, data1 REAL, data2 REAL, data3 REAL, data4 REAL, data5 REAL, data6 REAL);", tableName); //create create table statement TODO: how many float datacolumns?
		ret = sqlite3_exec(db, statementString, NULL, NULL, NULL);
		if(ret == SQLITE_OK){
			dlog_print(DLOG_INFO, LOG_TAG, "CREATED/OPENED TABLE %s", tableName); //print info
			openedTable = true;
		}else{
			dlog_print(DLOG_ERROR, LOG_TAG, "COULD NOT CREATE TABLE %s, ERROR CODE: %i ", tableName, ret); //print info
		}
		sqlite3_free(statementString);
	}else{
		dlog_print(DLOG_INFO, LOG_TAG, "TABLE %s HAS ALREADY BEEN CREATED/OPENED", tableName); //print info
	}
	return ret;
}
