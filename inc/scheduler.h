/**
 * @file scheduler.h
 * @brief Contains implementation of a simple class that enable scheduling of schedule_units.
 */

/*	Scheduler - Wouter Stokman - 2025418@umail.leidenuniv.nl
 * Contains implementation of a simple class that enable scheduling of schedule_units.
 * Scheduler is called every x seconds, where x is the time in seconds, given when calling scheduler_start_main_ecore_loop(x)
 * This ensures that the scheduler_update function is called every x seconds with the current time
 *
 * When a schedule_unit is due to be executed (unit.timestamp < curtime during a call to scheduler_update), the callback function that is specified in the schedule_unit is called, along with a pointer to the to-be-executed schedule_unit
 *
 * After this, the schedule unit is deleted from the scheduler, after which it can be manually re-added in the callback function to repeatedly reschedule and re-execute a schedule unit (e.g. execute every 10 seconds).
 *
 *
 *
 *
 * Example:
 *
 * void simpleCallback(schedule_unit * unit){
 * 	printf(unit.nparam); //prints the number of parameters of the unit that is being executed
 * 	unit.timestamp+=1000; //execute the unit in a second
 * 	scheduler_insert(unit); //insert a new copy of the unit into the scheduler so it will be executed again, the executed unit will be deleted after this
 *
 * }
 *
 *
 * schedule_unit unit;
 * unit.id = scheduler_get_new_unit_id(); //call this function to get a new ID that has not been used before (enabling safe deletion by id)
 * unit.unit_execute_function = simpleCallback; //set the callback function
 * unit.nparam = .....; //number of parameters
 * unit.path = .....  //set path here
 * unit.param = .....  //set param here
 * unit.timestamp = curtime + 1000; //Curtime=milliseconds since epoch, this will ensure unit will be executed one seconds from now
 *
 * scheduler_initialize(); //initialize the scheduler
 * scheduler_start_main_encore_loop(1.5); //update scheduler every 1.5 seconds
 * scheduler_insert(&unit); //insert a copy of the created unit in the scheduler
 *	//This is all that needs to be done, new schedule units can then be added/deleted
 *
 */



#include "stdbool.h"
#include <sys/time.h> //for time getting
#include <Ecore.h> //ecore
#include <dlog.h> //dlog
#include "protocol.h"

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



/*
 * @brief: Initializes the scheduler, should be called when using the scheduler
 * @params: none
 */
bool scheduler_initialize();


/*
 * @brief: Reset/finalize the scheduler
 * @params: none
 */
void scheduler_finalize();

/*
 * @brief: Add a schedule_unit to the scheduler
 * @params: the new schedule unit, a copy will be placed in the scheduler (the new unit should be deleted by the user
 */
void scheduler_unit_add(schedule_unit const * const new_unit);


/*
 * @brief: Remove a (first occurance of) scheduler unit with the passed id from the scheduler
 * @params: the id of the to-be-deleted schedule_unit
 * @return: if the removal was succesful (did the unit exist)
 */
bool scheduler_unit_id_remove(int unit_id);


/*
 * @brief: Print a single scheduler_unit
 * @params: the unit that needs to be printed
 */
void scheduler_print_unit(schedule_unit * unit);

/*
 * @brief: prints all schedule units, using scheduler_print_unit
 * @params: none
 */
void print_schedule();


/*
* @brief: stops the main ecore loop for the scheduler and deletes the timer
* @params: intervalInSec the amount of seconds between scheduler updates
*/
void scheduler_stop_main_ecore_loop();


/*
* @brief: start the main ecore loop for the scheduler, which will update the program every intervalInSec seconds
* @params: intervalInSec the amound of seconds between scheduler updates
*/
void scheduler_start_main_ecore_loop(double intervalInSec);



