/*
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

#if !defined(_DATA_H)
#define _DATA_H

#include <sensor.h>

#ifdef  LOG_TAG	//Logging purposes
#undef  LOG_TAG
#endif
#define LOG_TAG "sensorbasicui"

//DEFINES: (were originally in data.c)
#define SENSOR_COUNT 15
#define MAX_VALUES_PER_SENSOR 4

#define MAX_GYRO_VALUE 571.0
#define MAX_HRM_VALUE 220.0
#define LISTENER_TIMEOUT 0
#define LISTENER_TIMEOUT_FINAL ((LISTENER_TIMEOUT != 0) ? LISTENER_TIMEOUT : 100)

//ADDED (WAS IN C BEFORE)
typedef void (*Update_Sensor_Values_Cb)(sensor_type_e sensorType, sensor_event_s *event); //typedef of callback function for sensora

/**
 * Enable or disable a sensor
 * @param sensorNr          The sensor to configure
 * @param activity          Whether or not it is active
 */
void data_set_sensor_activity(sensor_type_e sensorNr, bool activity);

/**
 * Set the interval for a sensor
 * @param sensorNr          The sensor to configure
 * @param sensorIntervalMs  The measurement interval in milliseconds
 */
void  data_set_sensor_interval(sensor_type_e sensorNr, unsigned int sensorIntervalMs);

/**
 * Teardown sensor API
 */
void  data_finalize(void);

/**
 * Initialize sensor API
 * @param Update_Sensor_Values_Cb  Callback invoked when a sensor provides new data
 */
bool  data_initialize(Update_Sensor_Values_Cb callback);

/**
 * Check whether or not a given sensor is available on this device
 * @param sensorNr          The sensor to query
 */
bool  data_get_sensor_support(sensor_type_e type);

/**
 * Get the range for the sensor
 * @param sensorNr          The sensor to query
 * @param min               Output parameter returning the minimal value for a sensor
 * @param max               Output parameter returning the maximal value for a sensor
 */
void  data_get_sensor_range(sensor_type_e type, float *min, float *max);

/**
 * Get the resolution for a sensor
 * @param sensorNr          The sensor to query
 */
float data_get_sensor_resolution(sensor_type_e type);

/**
 * Get the vendor who provided the sensor
 * @param sensorNr          The sensor to query
 * @return                  The name of the vendor, should be freed by caller.
 */
char *data_get_sensor_vendor(sensor_type_e type);

extern const char  *sensor_strings[SENSOR_COUNT];

#endif
