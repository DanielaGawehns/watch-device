#include "sensorbasicui.h"

#include "data.h"//used for sensor support
#include "view.h"

#define MAX_SIZE_DATA_PATH 800

int
OpenDatabase();
int
CloseDatabase();

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
} appdata_s;


appdata_s * curAppdata;
void broadcast_hello() ;
static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}


static void
create_base_gui(appdata_s *ad)
{

	dlog_print(DLOG_INFO, LOG_TAG, "Started making the GUI, app has launched");
	curAppdata = ad;

	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
	ad->label = elm_label_add(ad->conform);
	elm_object_text_set(ad->label, "<align=center>Hello Tizen</align>");
	evas_object_size_hint_weight_set(ad->label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(ad->conform, ad->label);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

}

/**
 * @brief Gets the full path to a write/readable file in the datafolder (this does not check if it exists)
 * @param WriteFile: name of the file to get the full path from
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

/*
 * @brief creates a buffer with requested data from the database
 * @param sensorType of which data should be read in
 * @time1 1 of the between dates (data between time1 and time2 is requested)
 * @time2 2 of the between dates
 */
char *
get_sensor_data_from_database(sensor_type_e sensorType, const char * p_tableName, const char * time1, const char * time2){
	//Insert prepared datastring into the database
		/*if(openedTable){ //if table has not yet been opened (not sure whether it exists or not
			sqlite3_stmt statement;
			char *  statementString = sqlite3_mprintf("SELECT * FROM %Q WHERE sensor_name LIKE %s AND rec_data BETWEEN %s AND %s", p_tableName, sensor_strings[sensorType], time1, time2); //insert databuf into table
			int ret = sqlite3_prepare_v2(db, statementString, -1, &statement, NULL);

			while(ret == SQLITE_OK && sqlite3_step(stmt) != SQLITE_DONE){	//TODO: safe like this?
				int cols = sqlite3_column_count(stmt); //get amount of columns
				for(int i = 0; i < cols; i++){	//loop over cols
					//sqlite TODO: put data in struct? Or export whole database file and delete it?
				}
			}

			sqlite3_finalize(statement);
			//char *  statementString = sqlite3_mprintf("INSERT INTO %Q (sensor_name, data1, data2, data3, data4, data5) VALUES (%s)", p_tableName, dataBuf); //insert databuf into table
			if(ret == SQLITE_OK){
				dlog_print(DLOG_INFO, LOG_TAG, "SUCCESFULLY EXECUTED: %s", statementString);
			}else{
				dlog_print(DLOG_ERROR, LOG_TAG, "COULD NOT INSERT SENSORDATA IN TABLE %s, ERROR CODE: %i, QUERY: %s ", p_tableName, ret, statementString); //print info
			}
		}else{
			dlog_print(DLOG_ERROR, LOG_TAG, "TABLE %s WAS NOT OPENED, COULD NOT INSERT SENSORDATA", p_tableName); //print info
		}
		free(statementString);
		return ret;*/
	return "a";
}


void
log_sensor_data_to_file(int count, float * valArr,  sensor_type_e sensorType){
	char dataBuf[2000]; //create buffer for storing the sensor data
	char * filePath = get_filepath("sensordata.csv");	//create file name
	FILE * writeFile = fopen(filePath, "a"); //open a file in datapath called "testfile.csv", at the end (appending)
	if(writeFile == NULL){
		dlog_print(DLOG_ERROR, LOG_TAG, "Error opening file to write sensor data on path: %s", filePath);
		return;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Opened file path: %s", filePath);

	//get the time
	time_t theTime;
	struct tm * timeInfo;
	time(&theTime); //get the time
	timeInfo = localtime(&theTime);

	snprintf(dataBuf, sizeof(dataBuf), "%s,",sensor_strings[sensorType]); //put sensortype, into databuffer
	strftime(dataBuf + strlen(dataBuf), sizeof(dataBuf), "%Y-%m-%d,%H:%M:%S,", timeInfo); //put day, time, into databuffer

	for(int i = 0 ; i < count; i++){
		snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf), "%f,", valArr[i]); //write all sensordata into buffer
	}
	snprintf(dataBuf + strlen(dataBuf), sizeof(dataBuf), "\n"); //add nextline char
	fprintf(writeFile, "%s", dataBuf); //write buffer into file
	fclose(writeFile); //close file

	free(filePath); //TODO: check if no memory leaks for long term app runs
	dlog_print(DLOG_INFO, LOG_TAG, "Wrote to file: %s", dataBuf);

	dlog_print(DLOG_INFO, LOG_TAG, "Done with sensor update callback function", filePath);
}

void
Handle_Sensor_Update_Cb(sensor_type_e sensorType, sensor_event_s *ev){	//function for handling sensor input:

	//dlog_print(DLOG_INFO, LOG_TAG, "Calling the sensor update callback function:");
	//TODO:log_sensor_data_to_file(count, valArr, sensorType); //log to file
	//OpenTable(); //open the table
	//InsertDataInDatabase(count, valArr, sensorType); //insert sensordata into sqlite database
}




static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */

	//ADDED:
	data_initialize(Handle_Sensor_Update_Cb);	//set sensor data class
	OpenDatabase(); //open the database TODO: keep it opened?
	//-----------------------------

	//ADDED:
	view_create(); //initialize view
	view_switch_view(1);
	//------------------------------

	//ORIGINAL:
	//appdata_s *ad = data;
	//create_base_gui(ad);
	//-------
	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };
	 broadcast_hello() ;
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;



	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
