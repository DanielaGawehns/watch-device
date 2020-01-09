
#include <stdbool.h>
#include "protocol.h"
#include <sys/time.h> //for time getting
#include <Ecore.h> //ecore
#include <dlog.h> //dlog


#define SENSORRESERVED 50 //reserve 50 items for sensor types (as of 2019, only about 30 sensors exist)

//predefs
struct schedule_unit;
typedef struct schedule_unit schedule_unit;

//public functions
bool scheduler_initialize();
void scheduler_insert(schedule_unit * unit);
void scheduler_finalize();
void print_schedule();
void scheduler_start_main_ecore_loop(double intervalInSec);
void scheduler_unit_add(schedule_unit const * const new_unit);
void scheduler_print_unit(schedule_unit * unit);
void scheduler_data_set_sensor_activity_and_interval(schedule_unit * sensor_unit);
unsigned long long int scheduler_get_new_unit_id();


//tests //todo: remove
void scheduler_repeatedprocesstest(schedule_unit * repeat_unit);
void scheduler_keyval_set(schedule_unit * unit);

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



//int inuseCount[SENSORRESERVED] = {0,}; //keeps track of if more than 1 
//int secondLowestInterval[SENSORRESERVED] = {0,}; //Keeps track of the second lowest interval (used to set to when lowest interval on sensor is stopped)



struct schedule_unit{
    /*
     * unsigned long long int timestamp
     * when to execute this schedule unit
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    unsigned long long int timestamp;
    

    /*
     * Unit id
     * Used for referencing this unit, unit_id is the same for a pair
     * !: 0 is reserved for uninitialized schedule units
     */
    int unit_id;



	/*
	 * unit_execute_function
	 * Function that is called when this schedule unit is executed, only executed if specified (not NULL)
	 * May be used to re-insert this schedule unit into the schedule after execution
	 */
    void (*unit_execute_function)(schedule_unit * param);




	/*
	 * path
	 * path for setting - Used when setting keyval - see int keyval_set(...), protocol.md
	 */
    char * path;

    /*
     * nparam
     * Number of parameters for keyval setting - see int keyval_set(...), protocol.md
     */
    int nparam;


    /*
     * *param
     * Parameter array - see int keyval_set(...), protocol.md
     */
    message_param * param;

};



