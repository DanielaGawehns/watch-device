
#include "stdbool.h"

#define SENSORRESERVED 50 //reserve 50 items for sensor types (as of 2019, only about 30 sensors exist)

//predefs
struct schedule_unit;
typedef struct schedule_unit schedule_unit;

/**
* Scheduler
* Data used for the scheduler
*/
typedef struct{
    unsigned int id_counter;
    schedule_unit * arr; //array of all units
    int size; //current size
    int unitcount;
    bool active; //whether scheduler is active or not
} scheduler;

/**
 * @brief   Enumeration for unit targets,
 */
typedef enum
{
    TARGET_NONE = -2,
    //--------------------------------Source for base: Tizen library--------------------------------
	TARGET_SENSOR_ALL = -1,                        /**< All sensors. This can be used to retrieve #sensor_h for all available sensors. */
	TARGET_SENSOR_ACCELEROMETER,                   /**< Accelerometer */
	TARGET_SENSOR_GRAVITY,                         /**< Gravity sensor */
	TARGET_SENSOR_LINEAR_ACCELERATION,             /**< Linear acceleration sensor */
	TARGET_SENSOR_MAGNETIC,                        /**< Magnetic sensor */
	TARGET_SENSOR_ROTATION_VECTOR,                 /**< Rotation vector sensor */
	TARGET_SENSOR_ORIENTATION,                     /**< Orientation sensor */
	TARGET_SENSOR_GYROSCOPE,                       /**< Gyroscope */
	TARGET_SENSOR_LIGHT,                           /**< Light sensor */
	TARGET_SENSOR_PROXIMITY,                       /**< Proximity sensor */
	TARGET_SENSOR_PRESSURE,                        /**< Pressure sensor */
	TARGET_SENSOR_ULTRAVIOLET,                     /**< Ultraviolet sensor */
	TARGET_SENSOR_TEMPERATURE,                     /**< Temperature sensor */
	TARGET_SENSOR_HUMIDITY,                        /**< Humidity sensor */
	TARGET_SENSOR_HRM,                             /**< Heart-rate monitor @if MOBILE (Since 2.3.1) @endif
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HRM_LED_GREEN,                   /**< Green LED sensor of HRM @if MOBILE (Since 2.3.1) @endif
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HRM_LED_IR,                      /**< Infra-Red LED sensor of HRM @if MOBILE (Since 2.3.1) @endif
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HRM_LED_RED,                     /**< Red LED sensor of HRM @if MOBILE (Since 2.3.1) @endif
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_GYROSCOPE_UNCALIBRATED,          /**< Uncalibrated Gyroscope sensor
	                                             @if MOBILE (Since 2.4) @elseif WEARABLE (Since 2.3.2) @endif */
	TARGET_SENSOR_GEOMAGNETIC_UNCALIBRATED,        /**< Uncalibrated Geomagnetic sensor
	                                             @if MOBILE (Since 2.4) @elseif WEARABLE (Since 2.3.2) @endif */
	TARGET_SENSOR_GYROSCOPE_ROTATION_VECTOR,       /**< Gyroscope-based rotation vector sensor
	                                             @if MOBILE (Since 2.4) @elseif WEARABLE (Since 2.3.2) @endif */
	TARGET_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,     /**< Geomagnetic-based rotation vector sensor
	                                             @if MOBILE (Since 2.4) @elseif WEARABLE (Since 2.3.2) @endif */
	TARGET_SENSOR_SIGNIFICANT_MOTION = 0x100,      /**< Significant motion sensor (Since 4.0) */
	TARGET_SENSOR_HUMAN_PEDOMETER = 0x300,         /**< Pedometer (Since 3.0)
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HUMAN_SLEEP_MONITOR,             /**< Sleep monitor (Since 3.0)
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HUMAN_SLEEP_DETECTOR,            /**< Sleep detector (Since 3.0)
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_HUMAN_STRESS_MONITOR,            /**< Stress monitor (Since 3.0)
	                                             @n Privilege : http://tizen.org/privilege/healthinfo */
	TARGET_SENSOR_LAST,                            /**< End of sensor enum values (Deprecated since 3.0) */
	TARGET_SENSOR_CUSTOM = 0x2710,                 /**< Custom sensor (Deprecated since 3.0) */
    //--------------------------------Source: Tizen library--------------------------------
    // TODO: add custom targets here

} unit_target;

//int inuseCount[SENSORRESERVED] = {0,}; //keeps track of if more than 1 
//int secondLowestInterval[SENSORRESERVED] = {0,}; //Keeps track of the second lowest interval (used to set to when lowest interval on sensor is stopped)

struct schedule_unit{
        /**
     * Data timestamp
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int timestamp;
    


    /*
    * Unit id
    * Used for referencing this unit, unit_id is the same for a pair
    * !: 0 is reserved for uninitialized schedule units
    */
    int unit_id;


    /* 
    * Target id
    * First -1 <-> 50 id's are reserverd for sensors, specify which device the action_id will act upon (-1 is all sensors)
    */
    unit_target unit_target_id; 

    /*
    * Unit Action ID
    * Specifies which action should be taken when scheduler reaches this unit (-1 is no target)
    */
    int unit_action_id;

    /*
    * data
    * 5 specifications can be saved in each unit (e.a. measurement interval etc.)
    */
    int data[5]; 
    
};



