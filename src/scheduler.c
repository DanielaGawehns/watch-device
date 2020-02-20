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
 * After this, the schedule unit is deleted from the scheduler, after which it can be manually re-added in the callback function to repeatedly execute a schedule unit.
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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"
#include "data.h"
#include <Ecore.h> //ecore
#include "keyval.h"

#define LOG_TAG "sensorbasicui"

#define SCHEDULESIZEINCREASE 200 //Data increase per time the scheduler array is too small


void scheduler_keyval_set(schedule_unit * unit){
	 char *err;
	 keyval_set(unit->path, &err, unit->nparam, unit->param); //execute unit keyval_set action
	 unit->nparam +=1;
	 unit->timestamp += 1000;
	 scheduler_unit_add(unit);
}


/**
* @Brief scheduler_data
* Data used for the scheduler
*/
static scheduler scheduler_data = {
    .id_counter = 1, //start with first id =1
    .arr = NULL,
    .size = 0,
    .unitcount = 0,
    .active = false, //todo: necessary?
	.timer = NULL//used for main-loop
};


/*
 * @brief: Resets the scheduler, all schedule units will be deleted and the scheduler timer will be reset
 * @params: none
 */
void scheduler_reset(){ //resets scheduler to default
    scheduler_data.id_counter = 1;
    scheduler_data.unitcount = 0;
    scheduler_data.size = 0;
    scheduler_data.active = false;
    free(scheduler_data.arr);

	ecore_timer_del(scheduler_data.timer);
    scheduler_data.timer = NULL;
}

/*
 * @brief: Gets a new id for a to-be-added unit
 * @params: none
 */
long long unsigned int scheduler_get_new_unit_id(){
    unsigned cur = scheduler_data.id_counter;
    scheduler_data.id_counter += 1;
    return cur;
}

/*
 * @brief: Initializes the scheduler, should be called when using the scheduler
 * @params: none
 */
bool scheduler_initialize(){
    //TODO: initialization needed?
    return true;
}


/*
 * @brief: Reset/finalize the scheduler
 * @params: none
 */
void scheduler_finalize(){
    scheduler_data.id_counter = 1;
    scheduler_data.unitcount = 0;
    scheduler_data.size = 0;
    scheduler_data.active = false;
    free(scheduler_data.arr);
	ecore_timer_del(scheduler_data.timer);
    scheduler_data.timer = NULL;
}


/*
* @brief: pushes the schedule array one forward or backwards
* @params: index The index that will me moved   offset how much the index will be moved, this should be either 1 or -1, this function is not testing wether the push is safe (e.a. push 0 to -1)
*/ 
void scheduler_push(int index, int offset){
    memmove(&scheduler_data.arr[index + offset], &scheduler_data.arr[index], sizeof(schedule_unit) * (scheduler_data.unitcount - index) + 1); //push all units offset back/forward, always take the padding unit with id 0 along
}



/*
 * @brief: Increase the size of the scheduler, used to create space for new schedule units
 * @params: none
 */
void scheduler_increase_size(){
	dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Increasing scheduler allocation size", __FILE__, __LINE__ );
    scheduler_data.size = SCHEDULESIZEINCREASE + scheduler_data.size - 1; //always leave a padding unit 
    schedule_unit * new_arr = malloc(scheduler_data.size * sizeof(schedule_unit)); //allocate enough space
    for(int i = 0; i < scheduler_data.size; i++)
        new_arr[i].unit_id = 0; //initialize id to 0 to signal it as being uninitialized
    memcpy(new_arr, scheduler_data.arr, scheduler_data.unitcount * sizeof(schedule_unit)); //copy all filled units over to new buffer
    free(scheduler_data.arr);
    scheduler_data.arr = new_arr; 
}


/*
 * @brief: Add a schedule_unit to the scheduler
 * @params: the new schedule unit, a copy will be placed in the scheduler (the new unit should be deleted by the user
 */
void scheduler_unit_add(schedule_unit const * const new_unit){
    if(scheduler_data.unitcount + 1 > scheduler_data.size){ //if no longer enough size in scheduler
        scheduler_increase_size(); 
    }

    int i = 0; 
    for(; i < scheduler_data.unitcount; i++){
        if(scheduler_data.arr[i].unit_id == 0) //if empty (unit_id 0 is empty scheduler unit)
            break;
        if(scheduler_data.arr[i].timestamp > new_unit->timestamp){
            scheduler_push(i, 1); //index i becomes i+1
            break;
        }

    }
    scheduler_data.arr[i] = *new_unit;
    scheduler_data.unitcount++;
}

/*
 * @brief: Remove a unit by index
 * @params: the index of the schedule unit that needs to be removed
 */
void scheduler_unit_index_remove(int index){
    if(index < 0 || index > scheduler_data.unitcount) //if out of bounds index
        return;
    scheduler_push(index+1, -1); 
    scheduler_data.unitcount-=1; 
}



/*
 * @brief: Remove a scheduler unit with the passed id from the scheduler
 * @params: the id of the to-be-deleted schedule_unit
 * @return: if the removal was succesful (did the unit exist)
 */
bool scheduler_unit_id_remove(int unit_id){
    for(int i = 0; i < scheduler_data.unitcount; i++){
        if(scheduler_data.arr[i].unit_id == unit_id){ //check if object found
            scheduler_push(i+1, -1); 
            scheduler_data.unitcount-=1; 
            return true;
        }
    }
    return false;
}


/*
 * @brief: Print a single scheduler_unit
 * @params: the unit that needs to be printed
 */
void scheduler_print_unit(schedule_unit * unit){
	dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] ID: %i  -  TIMESTAMP: %llu   -  PATH:  %s  -  NPARAM:  %i  -  PARAM: TODO?", __FILE__, __LINE__, unit->unit_id, unit->timestamp, unit->path);
}

/*
 * @brief: Executes a schedule_unit, then removes it from the schedule (can be manually re-added)
 * @params: none
 */
 void scheduler_execute_unit(schedule_unit * unit){
	 if(!unit){
		 dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Error executing unit: no unit specified", __FILE__, __LINE__);
		 return;
	 }

	 dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Executing unit with id: %i", __FILE__, __LINE__, unit->unit_id);

	 if(!unit->unit_execute_function){
		 dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Error executing function in schedule unit %i, none specified", __FILE__, __LINE__, unit->unit_id);
		 return;
	 }
	//dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Executing function", __FILE__, __LINE__);

	 unit->unit_execute_function(unit); //run execute function
 }

/*
 * @brief: prints all schedule units, using scheduler_print_unit
 * @params: none
 */
void print_schedule(){
	 for(int i = 0; i < scheduler_data.unitcount; i++){
		 scheduler_print_unit(&scheduler_data.arr[i]);
	 }
}


/*
* @brief: updates the scheduler, using the current time
* @params: cur_time the current time (time since last epoch) in milliseconds
*/
void scheduler_update(long long int cur_time){
    for(int i = 0; i < scheduler_data.unitcount;){ //if unit is executed, it is also deleted so no need to increase i
        if(scheduler_data.arr[i].timestamp < cur_time){
        	schedule_unit temp = scheduler_data.arr[i]; //temp copy
            scheduler_unit_index_remove(i); //remove the unit by index (NOT by ID since the scheduler can be re-added)
            scheduler_execute_unit(&temp); //execute this unit
        }else{ //since it is sorted -> stop when first not-to-be-executed unit is encountered
            break;
        }
    }
}



/*
* @brief: the main ecore loop, this updates the scheduler by generating the current time and calling scheduler_update
* @params: data data pointer, is not used (is needed because this is an ecore function)
*/
Eina_Bool scheduler_ecore_loop(void *data){
    struct timeval timeValue;
    gettimeofday(&timeValue, NULL);
    unsigned long long cur_time = (unsigned long long)(timeValue.tv_sec) * 1000 + (unsigned long long)(timeValue.tv_usec) / 1000; //get current time in milliseconds from start of epoch
   // dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Updating scheduler with time %llu, units remaining: %i", __FILE__, __LINE__, cur_time, scheduler_data.unitcount);
    scheduler_update((long long int) cur_time); //update scheduler with the current time

    return ECORE_CALLBACK_RENEW; //renew ecore timer
}


/*
* @brief: stops the main ecore loop for the scheduler and deletes the timer
* @params: intervalInSec the amount of seconds between scheduler updates
*/
void scheduler_stop_main_ecore_loop(){
    if(scheduler_data.timer != NULL){
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Stopping ecore timer for scheduler", __FILE__, __LINE__);
    }

    if (scheduler_data.timer) {
		ecore_timer_del(scheduler_data.timer);
		scheduler_data.timer = NULL;
	}

}


/*
* @brief: start the main ecore loop for the scheduler, which will update the program every intervalInSec seconds
* @params: intervalInSec the amound of seconds between scheduler updates
*/
void scheduler_start_main_ecore_loop(double intervalInSec){
    if(scheduler_data.timer != NULL){
        dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Overwriting current ecore main loop with new interval %f", __FILE__, __LINE__, intervalInSec);
        scheduler_stop_main_ecore_loop();
    }else{
    	dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Starting scheduler main encore loop with interval %f", __FILE__, __LINE__, intervalInSec);
    }
    print_schedule();
    scheduler_data.timer = ecore_timer_add(intervalInSec, scheduler_ecore_loop, NULL);
}




