#include "sensorbasicui.h"
#include "data.h" //used for sensor support
#include "view.h"
#include <device/power.h>
#include "scheduler.h"
#include "protocol.h"
#include "network.h"
#include <sqlite3.h> //used for database
#include "netcore.h"

#define MAX_SIZE_DATA_PATH 800

int
OpenDatabase();

int
CloseDatabase();

int
OpenTable();

int
InsertDataInDatabase();

char*
GetDataFromDatabase();

typedef struct data datatest; //refer to struct data with type data

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
} appdata_s;


appdata_s * curAppdata;

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

/**
 * @brief creates the gui for the watchface
 * @param ad application data
 */

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
 * @brief writes sensor data to the sensordata.csv file in the datafolder of the watch
 * @param count amount of fields in the data
 * @param valArr pointer to the data from the sensor
 * @param sensorType name of the sensor that wants to log data
 */
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

/**
 * @brief function that is called when a sensor records data
 * @param sensorType name of the sensor that wants to log data
 * @param ev contains the data from the sensor
 */
void
Handle_Sensor_Update_Cb(sensor_type_e sensorType, sensor_event_s *ev){	//function for handling sensor input:
	int count = 0;
	//dlog_print(DLOG_INFO, LOG_TAG, "Calling the sensor update callback function:");
	//OpenTable(); //open the table
	//InsertDataInDatabase(count, valArr, sensorType); //insert sensordata into sqlite database
	//TODO:log_sensor_data_to_file(count, valArr, sensorType); //log to file
	OpenTable(); //open the table
	switch (sensorType) {
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			count = 1;
			break;
		case 0:
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
			count = 3;
			break;
		case 4:
			count = 4;
			break;
		default:
			dlog_print(DLOG_ERROR, LOG_TAG, "Sensor Callback handle for %s could not be found", sensor_strings[sensorType]);
			break;
	}
	int writtenRows;
	InsertDataInDatabase(count, ev, sensorType); //insert sensordata into sqlite database
}

void init_syskv();

/**
 * @brief initialize function for view and sensor
 * @param data pointer to application data
 * @return success state
 */
static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */

	init_syskv();
	//ADDED:
	data_initialize(Handle_Sensor_Update_Cb);	//set sensor data class
	OpenDatabase(); //open the database TODO: keep it opened?
	//-----------------------------

	//ADDED:
//	view_create(); //initialize view
//	view_switch_view(1);
	//------------------------------





	//initialize scheduler data
	if(!scheduler_initialize()){
		dlog_print(DLOG_ERROR, LOG_TAG, "Error initializing scheduler");
	}

    struct timeval timeValue;
    gettimeofday(&timeValue, NULL);
    unsigned long long cur_time = (unsigned long long)(timeValue.tv_sec) * 1000 + (unsigned long long)(timeValue.tv_usec) / 1000; //get current time in milliseconds from start of epoch


	schedule_unit  newUnit; // = malloc( sizeof(schedule_unit));

	newUnit.unit_id = scheduler_get_new_unit_id(); //get id for unit

	char * temp = malloc(sizeof(char) * 10);
	temp = "test/path";

	newUnit.path = "test/path";
	newUnit.timestamp = cur_time;
	newUnit.nparam = 1;
	newUnit.unit_execute_function = scheduler_keyval_set;

	scheduler_unit_add(&newUnit);
	scheduler_unit_add(&newUnit);
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Done creating testunits", __FILE__, __LINE__);

	//Scheduler/ecore mainloop:
	scheduler_start_main_ecore_loop(1); //run ecore loop of scheduler every 1 second
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Done starting main ecore loop", __FILE__, __LINE__);

	//ORIGINAL:
	//appdata_s *ad = data;
	//create_base_gui(ad);
	//-------
	data_set_sensor_activity(0, 1);
	netcore_init();
	netcore_connect();

	return true;
}

/**
 * @brief handles launch request
 * @param app_control_h handle for handling launch requests from other applications
 * @param data pointer to application data
 */
static void
app_control(app_control_h app_control, void *data)
{
}

/**
 * @brief handles when application goes to the background
 * @param data pointer to application data
 */
static void
app_pause(void *data)
{
}

/**
 * @brief handles when application goes back to the foreground
 * @param data pointer to application data
 */
static void
app_resume(void *data)
{
}

/**
 * @brief handles when the application is exited
 * @param data pointer to application data
 */
static void
app_terminate(void *data)
{
	/* Release all resources. */
}

/**
 * @brief handles language change
 * @param event_info
 * @param user_data pointer to user data
 */
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

/**
 * @brief handles change of orientation of device
 * @param event_info
 * @param user_data pointer to user data
 */
static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

/**
 * @brief handles region change
 * @param event_info
 * @param user_data pointer to user data
 */
static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

/**
 * @brief handles when battery power becomes low
 * @param event_info
 * @param user_data pointer to user data
 */
static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

/**
 * @brief handles when watch is low on memory
 * @param event_info
 * @param user_data pointer to user data
 */
static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	/// Prevent OS from terminating app when OS requires more resources
	device_power_request_lock(POWER_LOCK_CPU, 0);
	appdata_s ad = {0,};
	int ret = 0;


	dlog_print(DLOG_INFO, LOG_TAG, "SQLITE THREADSAFETY: %i", sqlite3_threadsafe());


	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };
	//broadcast_hello() ;
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;


	//set event handlers
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
