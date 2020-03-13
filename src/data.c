/**
 * @file data.c
 * @date 10 Jan 2020
 * @brief File implementing the communication with the sensors on the watch device
 */

/*
 * This code is an alteration on the by Tizen Studio Provided sample code used in their sample apps.
 * All code from the original file is distributed under the license specified underneath this statement.
 * Some alterations to this file have been made, these do not fall under the same license.
 *
 *
 *
 * This class contains code to read out data from the sensors available on the device. A callback function needs to be passed, which will be called with the appropriate data when a sensor registers a value.
 * This class is PROBABLY NOT thread safe!
 *
 * ------------------------------------------------------------------------------------
 * Copyright (c) 2016 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Eina.h>
#include <app_preference.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <app_common.h>//for app_get_data_path
#include <stdio.h>
#include <math.h>
#include <sensor.h>
#include <tizen.h>
#include "data.h"
#include <Ecore.h> //ecore
#include <dlog.h>
#include "keyval.h"

/**
 * @brief String names for sensor_type_e values
 */
const char *sensor_strings[SENSOR_COUNT] = {
	"ACCELEROMETER",
	"GRAVITY",
	"LINEAR ACCELERATION",
	"MAGNETIC",
	"ROTATION VECTOR",
	"ORIENTATION",
	"GYROSCOPE",
	"LIGHT",
	"PROXIMITY",
	"PRESSURE",
	"ULTRAVIOLET",
	"TEMPERATURE",
	"HUMIDITY",
	"HRM",
	"STRING/SENSOR NOT ADDED"
};

/**
 *  @brief sensor data struct used to manage each sensor's listener and handle
 */
typedef struct _sensor_data {
	sensor_h handle;
	sensor_listener_h listener;
	keyval *kv_ns;
	keyval *kv_active;
	keyval *kv_interval;
	keyval *kv_name;
	keyval *kv_range;
	keyval *kv_resolution;
	sensor_type_e id;
	const char *name;
} sensor_data_t;

/**
 * @brief info on the status of sensors
 */
static struct data_info {
	sensor_type_e current_sensor;
	bool sensor_activity[SENSOR_COUNT];		//custom: for checking which sensors are active
	sensor_data_t sensors[SENSOR_COUNT];
	unsigned int sensor_interval_ms[SENSOR_COUNT]; 	//custom: interval for sensor checking
	Update_Sensor_Values_Cb sensor_update_cb;	//callback function that is called when a sensor reads new data, set when initializing this class at (data_initialize)
} s_info = {
	.sensors = { {0}, },
	.sensor_activity = { false, }, //custom: initialize sensors on inactive
	.sensor_interval_ms = { 0, },
	.current_sensor = 0,
	.sensor_update_cb = NULL,
};


/**
 * @brief predefinition
 */
static void _initialize_sensors(void);
/**
 * @brief predefinition
 */
static void _sensor_event_cb(sensor_h sensor, sensor_event_s *event, void *data);

/**
 * TODO: the functions hereafter are custom added, handy web: https://developer.tizen.org/dev-guide/2.3.1/org.tizen.tutorials/html/native/system/sensor_tutorial_n.htm
 */

/**
 * @brief sets a sensors activity, given the id and new activity (if sensor is available and status is not already the given status)
 * @param the sensor NR/id
 * @param new status of this sensor
 */
void data_set_sensor_activity(sensor_type_e sensorNr, bool activity){
	if(!activity){	//if sensor should be stopped
		int ret = sensor_listener_stop(s_info.sensors[sensorNr].listener);
		if (ret != SENSOR_ERROR_NONE) {
			dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_listener_stop() %s error: %s", __FILE__, __LINE__,  sensor_strings[sensorNr], get_error_message(ret));
			return;
		}
	}else{	//if sensor should be started
		int ret = sensor_listener_start(s_info.sensors[sensorNr].listener);	//start sensor
		if (ret != SENSOR_ERROR_NONE) { //if an error occured while starting the sensor
			dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_listener_start() %s error: %s", __FILE__, __LINE__,  sensor_strings[sensorNr], get_error_message(ret));
			return;
		}
	}
	s_info.sensor_activity[sensorNr] = activity; //set new activity

	dlog_print(DLOG_INFO, LOG_TAG, "Set activity of sensor: %s to %i", sensor_strings[sensorNr], activity);
}

/**
 * @brief sets a new check interval for a sensor
 * @param the sensor nr/enum/id
 * @param the new interval at which the sensor should be checked
 */
void data_set_sensor_interval(sensor_type_e sensorNr, unsigned int sensorIntervalMs){

	int ret = sensor_listener_set_interval(s_info.sensors[sensorNr].listener, sensorIntervalMs);

	if (ret != SENSOR_ERROR_NONE) { //if an error occured when setting the interval
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] set_sensor_interval error: %s", __FILE__, __LINE__, get_error_message(ret));
		return;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Set sensor interval of sensor: %s to: %i", sensor_strings[sensorNr], sensorIntervalMs);

	s_info.sensor_interval_ms[sensorNr] = sensorIntervalMs;
}

/**
 * @brief Function that initializes the data module.
 * @param sensor_update_cb Callback used to update the data displayed in the data view.
 * @return True on success or false on error.
 */

bool data_initialize(Update_Sensor_Values_Cb sensor_update_cb)
{
	_initialize_sensors();
	s_info.sensor_update_cb = sensor_update_cb;
	//temp_func(); //for debugging/testing purposes - TODO: delete

	dlog_print(DLOG_ERROR, LOG_TAG, "Initialized data", __FILE__, __LINE__);
	return true;
}


/**
 * @brief Function used to destroy the sensor listeners. Should be invoked when the app is terminated.
 */
void data_finalize(void)
{
	int ret = SENSOR_ERROR_NONE;
	int i;

	for (i = 0; i < SENSOR_COUNT; ++i) {
		ret = sensor_destroy_listener(s_info.sensors[i].listener);
		if (ret != SENSOR_ERROR_NONE) {
			dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_default_sensor() error: %s", __FILE__, __LINE__, get_error_message(ret));
			continue;
		}
	}
}

/**
 * @brief Checks if the given sensor type is supported by the device.
 * @param type The sensor's type.
 * @return true - sensor is supported, false - sensor is not supported.
 */
bool data_get_sensor_support(sensor_type_e type)
{
	bool supported = false;
	int ret;

	ret = sensor_is_supported(type, &supported);
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_is_supported() error: %s", __FILE__, __LINE__, get_error_message(ret));
		return false;
	}

	return supported;
}

/**
 * @brief Checks the minimal and maximal values that the given sensor supports.
 * @param type The sensor type.
 * @param[out] min The minimal value.
 * @param[out] max The maximal value.
 */
void data_get_sensor_range(sensor_type_e type, float *min, float *max)
{
	*min = 0;
	*max = 0;

	//TODO: Check why these are special cased
	if (type == SENSOR_GYROSCOPE) {
		*min = -MAX_GYRO_VALUE;
		*max = MAX_GYRO_VALUE;
		return;
	} else if (type == SENSOR_HRM) {
		*min = 0.0;
		*max = MAX_HRM_VALUE;
		return;
	}

	int ret = sensor_get_min_range(s_info.sensors[type].handle, min);
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_min_range() error: %s", __FILE__, __LINE__, get_error_message(ret));
		return;
	}

	ret = sensor_get_max_range(s_info.sensors[type].handle, max);
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_min_range() error: %s", __FILE__, __LINE__, get_error_message(ret));
		return;
	}
}

/**
 * @brief Checks the sensor's resolution.
 * @param type The sensor type.
 * @return The sensor's resolution.
 */
float data_get_sensor_resolution(sensor_type_e type)
{
	int ret;
	float resolution = 0.0;

	ret = sensor_get_resolution(s_info.sensors[type].handle, &resolution);
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_resolution() error: %s", __FILE__, __LINE__, get_error_message(ret));
		return 0.0;
	}

	return resolution;
}

/**
 * @brief Checks the sensor's vendor.
 * @param type The sensor type.
 * @return The sensor's vendor (the returned value should be freed).
 */
char *data_get_sensor_vendor(sensor_type_e type)
{
	int ret;
	char *vendor = NULL;

	ret = sensor_get_vendor(s_info.sensors[type].handle, &vendor);
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_vendor() error: %s", __FILE__, __LINE__, get_error_message(ret));
		return strdup("");
	}

	return vendor;
}


/**
 * @brief Callback invoked by a sensor's listener.
 * @param sensor The sensor's handle.
 * @param event The event data.
 * @param data The user data.
 */
static void _sensor_event_cb(sensor_h _sensor, sensor_event_s *event, void *data)	//TODO: seperate data storing from this function?
{

	sensor_data_t *sensor = data;

  if ( sensor->id == SENSOR_PRESSURE)
		event->value_count = 1; /* Why? */
	dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] got data for sensor", __FILE__, __LINE__ );
	s_info.sensor_update_cb( sensor->id, event );

}
/******************** start of sensor keyval implementation *******************/
/**
 * The root key for the sensor hierarchy
 */
static keyval *sensor_ns;

int kvdata_name_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	sensor_data_t *sensor = kv->impl;
	return prot_create_param_1s( status, nparam, param, sensor->name );
}

int kvdata_active_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	sensor_data_t *sensor = kv->impl;
	return prot_create_param_1i( status, nparam, param, s_info.sensor_activity[sensor->id] );
}

int kvdata_active_set( keyval *kv, char **status, int nparam, message_param *param )
{
	sensor_data_t *sensor = kv->impl;
	if ( nparam != 1 || param[0].length != sizeof(int) ) {
		*status = strdup( "Wrong arguments for sensor.active::set" );
		return KV_EINVAL;
	}
	data_set_sensor_activity( sensor->id, prot_decode_long(param[0].data) );
	return 0;
}

int kvdata_resolution_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	sensor_data_t *sensor = kv->impl;
	double res = data_get_sensor_resolution( sensor->id );
	return prot_create_param_1d( status, nparam, param, res );
}

int kvdata_range_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	sensor_data_t *sensor = kv->impl;
	float min, max;
	data_get_sensor_range( sensor->id, &min, &max );
	return prot_create_param_2d( status, nparam, param, min, max );
}

int kvdata_interval_get( keyval *kv, char **status, int *nparam, message_param **param )
{
	sensor_data_t *sensor = kv->impl;;
	return prot_create_param_1d( status, nparam, param, s_info.sensor_interval_ms[ sensor->id ] );
}

int kvdata_interval_set( keyval *kv, char **status, int nparam, message_param *param )
{
	sensor_data_t *sensor = kv->impl;
	if ( nparam != 1 || param[0].length != sizeof(double) ) {
		*status = strdup( "Wrong arguments for sensor.interval::set" );
		return KV_EINVAL;
	}
	data_set_sensor_interval( sensor->id, prot_decode_double(param[0].data)*1000. );
	return 0;
}



static void init_sensor( int i )
{
	int ret;
	sensor_data_t *sensor = s_info.sensors + i;

	/* Setup sensor fields */
	sensor->id = i;
	sensor->name = sensor_strings[i];

	/* Allocate keyval namespace */
	sensor->kv_ns = keyval_create_ns( sensor->name );
	if ( !sensor->kv_ns ) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] keyval_create_ns() error %s", __FILE__, __LINE__, sensor->name );
		return;
	}

	/* Register keyval namespace */
	ret = keyval_add_k( sensor_ns, sensor->kv_ns );
	if ( ret < 0 ) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] keyval_add_k() error %s", __FILE__, __LINE__, sensor->name );
		return;
	}

	sensor->kv_active     = keyval_create_add_k_leaf( sensor->kv_ns, "active"    , "bool"     , kvdata_active_get    , kvdata_active_set  , sensor );
	sensor->kv_interval   = keyval_create_add_k_leaf( sensor->kv_ns, "interval"  , "double"   , kvdata_interval_get  , kvdata_interval_set, sensor );
	sensor->kv_name       = keyval_create_add_k_leaf( sensor->kv_ns, "name"      , "string"   , kvdata_name_get      , NULL               , sensor );
	sensor->kv_range      = keyval_create_add_k_leaf( sensor->kv_ns, "range"     , "double[2]", kvdata_range_get     , NULL               , sensor );
	sensor->kv_resolution = keyval_create_add_k_leaf( sensor->kv_ns, "resolution", "double"   , kvdata_resolution_get, NULL               , sensor );
	if ( !(sensor->kv_active && sensor->kv_interval && sensor->kv_name && sensor->kv_range && sensor->kv_resolution) ) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] keyval_add_leaf() error %s", __FILE__, __LINE__, sensor->name );
		return;
	}

	/* Request a handle to the sensor */
	ret = sensor_get_default_sensor( i, &sensor->handle );	//get a handle to the sensor
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_get_default_sensor() error %s: %s", __FILE__, __LINE__, sensor->name, get_error_message(ret) );
		return;
	}

	ret = sensor_create_listener( sensor->handle, &sensor->listener );	//link the appropriate listener to the sensor using the sensor handle
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print( DLOG_ERROR, LOG_TAG, "[%s:%d] sensor_create_listener() error %s: %s", __FILE__, __LINE__, sensor->name, get_error_message(ret) );
		return;
	}

	sensor_listener_set_option( sensor->listener, SENSOR_OPTION_ALWAYS_ON ); //keep sensors on
				///sensor_listener_set_option (s_info.sensors[i].listener, SENSOR_OPTION_ON_IN_SCREEN_OFF); //keep sensors on when screen is off
	//TODO: make sure this option is not reverted when sensor is turned off then on again

  /* Set the sensor listener callback to be _sensor_event_cb( sensor ) */
	ret = sensor_listener_set_event_cb(
                                      sensor->listener, 
                                      LISTENER_TIMEOUT, 
                                      _sensor_event_cb, 
                                      sensor );
	if (ret != SENSOR_ERROR_NONE) {
		dlog_print( DLOG_ERROR, LOG_TAG, 
                "[%s:%d] sensor_listener_set_event_cb() error %s: %s", 
                __FILE__, __LINE__, 
                sensor->name, 
                get_error_message(ret) );
		return;
	}
}

/**
 * @brief Initializes the sensors. The function sets the handles and creates a listener for each of the sensors.
 */
static void _initialize_sensors(void)
{
	int i,ret;
	sensor_ns = keyval_create_ns( "sensor" );
	if ( !sensor_ns ) {
		dlog_print( DLOG_ERROR, LOG_TAG, 
                "[%s:%d] keyval_create_ns() error \"sensor\"",
                __FILE__, __LINE__ );
		return;
	}

	/* Register keyval namespace */
	ret = keyval_add_p( "", sensor_ns );
	if ( ret < 0 ) {
		dlog_print( DLOG_ERROR, LOG_TAG, 
                "[%s:%d] keyval_add_k() error  \"sensor\"",
                __FILE__, __LINE__ );
		return;
	}

	for (i = 0; i < SENSOR_COUNT; ++i) {
		init_sensor( i );
	}
}
