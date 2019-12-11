#include "sensorbasicui.h"
#include "data.h"//used for sensor support
#include <sqlite3.h> //used for database

//------------------------------ Temporary database constans
 /* Buffer size, used in functions */
#define BUFLEN 800
 /* AES key length */
const int key_len = 256;

/* Password to generate key */
static const unsigned char password[] = {"DummyPassword"};
static const unsigned char tableName[] = {"DataTable"};
const int dbDataCols = 5;

sqlite3 *db; /* Database handle */
bool openedDatabase = false; //opened database
bool openedTable = false; //made sure data table exists
unsigned char salt[9]; /* Encryption salt */
unsigned char iv[17]; /* Encryption initial vector */
//----------------------------------

/**
 * @brief Gets the full path to a write/readable file in the datafolder (this does not check if it exists)
 * @param WriteFile: name of the file to get the full path from
 */
extern char * get_filepath(char * writeFile);

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
		ret = sqlite3_open(dbPath, &db); //open database
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
InsertDataInDatabase(int count, float * valArr,  sensor_type_e sensorType){
	char dataBuf[2000]; //create buffer for storing the sensor data
	int ret = SQLITE_OK; //return value

	struct tm * timeInfo;
	struct timeval timeValue;
	gettimeofday(&timeValue, NULL);
	timeInfo = localtime(&timeValue.tv_sec);


	snprintf(dataBuf, sizeof(dataBuf), "\'%s\'",sensor_strings[sensorType]); //put sensortype, into databuffer
	strftime(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",\'%Y-%m-%dT%H:%M:%S", timeInfo); //put day, time (h:m:s) into databuffer
	snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ".%i\'", (int) (timeValue.tv_usec / 1000));

	for(int i = 0 ; i < 3; i++){ //TODO: make sure amount of columns is not exceeded?
		snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",%f", valArr[i]); //write all sensordata into buffer
	}
	for(int i = count; i < dbDataCols; i++){ //append ',' until all cols are filled	TODO: also edit when making amount of cols modular
		snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf) - strlen(dataBuf), ",0" );
	}

	//Insert prepared datastring into the database
	if(openedTable){ //if table has not yet been opened (not sure whether it exists or not
		char *  statementString = sqlite3_mprintf("INSERT INTO %Q (sensor_name, rec_date, data1, data2, data3, data4, data5) VALUES (%s)", tableName, dataBuf); //insert databuf into table
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
 * @brief open a table within the database
 * @return succes state
 */
int
OpenTable(){
	char * statementString; // = sqlite3_mprintf("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='{%Q}'", tableName); //create statement using opened tablename : if table exists, count >0
	int ret = SQLITE_OK; //return value
	if(!openedTable || true){ //if table has not yet been opened (not sure whether it exists or not
		statementString = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS %s(sensor_name TEXT, rec_date DATE, data1 REAL, data2 REAL, data3 REAL, data4 REAL, data5 REAL);", tableName); //create create table statement TODO: how many float datacolumns?
		ret = sqlite3_exec(db, statementString, NULL, NULL, NULL);
		if(ret == SQLITE_OK){
			dlog_print(DLOG_INFO, LOG_TAG, "CREATED/OPENED TABLE %s", tableName); //print info
			openedTable = true;
		}else{
			dlog_print(DLOG_ERROR, LOG_TAG, "COULD NOT CREATE TABLE %s, ERROR CODE: %i ", tableName, ret); //print info
		}
		sqlite3_free(statementString);(statementString); //TODO Memory leak
	}else{
		dlog_print(DLOG_INFO, LOG_TAG, "TABLE %s HAS ALREADY BEEN CREATED/OPENED", tableName); //print info
	}
	return ret;
}
