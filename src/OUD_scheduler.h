#if false
#include "stdbool.h"
#include <sys/time.h> //for time getting
#include <Ecore.h> //ecore
#include <Tizen.h>
#include <dlog.h> //dlog


#define SENSORRESERVED 50 //reserve 50 items for sensor types (as of 2019, only about 30 sensors exist)

//predefs
struct schedule_unit;
typedef struct schedule_unit schedule_unit;

//public functions
bool scheduler_initialize();
void scheduler_finalize();
void print_schedule();
void scheduler_start_main_ecore_loop(double intervalInSec);
void scheduler_unit_add(schedule_unit * new_unit);
void scheduler_print_unit(schedule_unit * unit);
void scheduler_data_set_sensor_activity_and_interval(schedule_unit * sensor_unit);
long long unsigned int scheduler_get_new_unit_id();
void scheduler_repeatedprocesstest(schedule_unit * repeat_unit);
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
	Ecore_Timer *timer; //used for main loop
} scheduler;



/**
 * @brief   Enumeration for unit targets,
 */
typedef enum
{
	TARGET_SENSOR_START = -3,
    TARGET_NONE = -2,
    //--------------------------------Source for base enum: sensor_type_e - Tizen library--------------------------------
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
	TARGET_SENSOR_LAST                            /**< End of sensor enum values (Deprecated since 3.0) */
    //--------------------------------Source: Tizen library--------------------------------
    // TODO: add custom targets here

} unit_target;

typedef enum
{
	ACTION_NONE = 0,
	ACTION_TURN_ON = 1,
	ACTION_TURN_OFF
	//TODO: add custom targets here
} unit_action;

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
     * unit_execute_function
     * Function that is called when this schedule unit is executed
     */
    void (*unit_execute_function)(schedule_unit * param);

    /*
    * Unit Action ID
    * Specifies which action should be taken when scheduler reaches this unit (-1 is no target)
    */
    int unit_action_id;

    //TODO: ------------------- UNION/ONLY 1?

    /*
     * repeats
     * Specifies how many repeats remain (-1 for infinite)
     */
    int repeats;

    /*
     * repeat_time
     * Specifies the amount of seconds that should be waited until next repeat
     */
    double repeat_time;

    /*
    * data
    * 5 specifications can be saved in each unit (e.a. measurement interval etc.)
    */
    int data[5]; 
    
    /*
     * data2
     * Extra (higher/lower range) data that can be saved in each unit
     */
    double data2[2];

};
#endif


