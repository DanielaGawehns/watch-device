
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"
#include "data.h"
#include <Ecore.h> //ecore
#include <Tizen.h>


#define SCHEDULESIZEINCREASE 200 //Data increase per time the scheduler array is too small

//for debgging purposes

/*
scheduler scheduler_data{
    .arr = NULL;
    .size = 0;
    .unitcount = 0;
    .active = false;
};*/

/**
* scheduler_data
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

void scheduler_reset(){ //resets scheduler to default
    scheduler_data.id_counter = 1;
    scheduler_data.unitcount = 0;
    scheduler_data.size = 0;
    scheduler_data.active = false;
    free(scheduler_data.arr);
    scheduler_data.timer = NULL;
}

long long unsigned int scheduler_get_new_unit_id(){
    unsigned cur = scheduler_data.id_counter;
    scheduler_data.id_counter += 1;
    return cur;
}

bool scheduler_initialize(){
    //TODO: initialization needed?
    return true;
}

void scheduler_finalize(){
    scheduler_data.id_counter = 1;
    scheduler_data.unitcount = 0;
    scheduler_data.size = 0;
    scheduler_data.active = false;
    free(scheduler_data.arr);
}


/*
* @brief: pushes the schedule array one forward or backwards
* @params: index The index that will me moved   offset how much the index will be moved, this should be either 1 or -1, this function is not testing wether the push is safe (e.a. push 0 to -1)
*/ 
void scheduler_push(int index, int offset){
    memmove(&scheduler_data.arr[index + offset], &scheduler_data.arr[index], sizeof(schedule_unit) * (scheduler_data.unitcount - index) + 1); //push all units offset back/forward, always take the padding unit with id 0 along
}


void scheduler_data_set_sensor_activity_and_interval(schedule_unit * sensor_unit){
	if(sensor_unit->unit_target_id < TARGET_SENSOR_START
			|| sensor_unit->unit_target_id > TARGET_SENSOR_LAST){
		dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Error: sensor target out of bounds", __FILE__, __LINE__ );
	}

	sensor_type_e sensorTarget = (int)sensor_unit->unit_target_id; //sensor_type_e translates directly to unit_target

	if(sensor_unit->unit_action_id == ACTION_TURN_ON){
		data_set_sensor_activity(sensorTarget, true); //turn on sensor
	} else if(sensor_unit->unit_action_id == ACTION_TURN_OFF){
		data_set_sensor_activity(sensorTarget, false);
	} else if(sensor_unit->unit_action_id != ACTION_NONE){
		dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Error: sensor action not valid, only turn on, off and no action are implemented", __FILE__, __LINE__ );
	}

	if(sensor_unit->data[0] > 0){ //if a new interval is specified
		data_set_sensor_interval(sensorTarget, (unsigned int) sensor_unit->data[0]);
	}
}

void scheduler_repeatedprocesstest(schedule_unit * repeat_unit){
	repeat_unit->data[0] -= 1;
	dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] %i iterations left", __FILE__, __LINE__, repeat_unit->data[0] + 1 );
	repeat_unit->unit_id = scheduler_get_new_unit_id(); //new id is not neccesary if no other unit exists, but just to be safe
	repeat_unit->timestamp += repeat_unit->data[1];
	if(repeat_unit->data[0] + 1> 0){
		scheduler_unit_add(repeat_unit);
	}
}

//void scheduler_data_set_sensor_interval(schedule_unit * sensor_unit){
//	if(sensor_activity_unit->unit_target_id < TARGET_SENSOR_START
//			|| sensor_activity_unit->unit_target_id > TARGET_SENSOR_LAST){
//		dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Error: sensor target out of bounds", __FILE__, __LINE__ ); //check if sensor id is out of bounds
//	}
//
//}


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

void scheduler_unit_add(schedule_unit * new_unit){
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

void scheduler_unit_index_remove(int index){
    if(index < 0 || index > scheduler_data.unitcount) //if out of bounds index
        return;
    scheduler_push(index+1, -1); 
    scheduler_data.unitcount-=1; 
}



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


void scheduler_print_unit(schedule_unit * unit){
	 dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] UNIT %i - Time: %lli - Target: %i - Action: %i", __FILE__, __LINE__, unit->unit_id, unit->timestamp, unit->unit_target_id, unit->unit_action_id);
}

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
	 unit->unit_execute_function(unit); //run execute function
 }


void print_schedule(){
	 for(int i = 0; i < scheduler_data.unitcount; i++){
		 scheduler_print_unit(&scheduler_data.arr[i]);
	 }

//    for(int i =0; i < scheduler_data.unitcount; i++){
//        printf("%i - Timestamp: %llu      ID: %i     Target:%s     Action:%i \n", i, scheduler_data.arr[i].timestamp, scheduler_data.arr[i].unit_id, sensor_strings[scheduler_data.arr[i].unit_target_id], scheduler_data.arr[i].unit_action_id);
//    }
}


/*
* @brief: updates the scheduler, using the current time
* @params: cur_time the current time (time since last epoch) in milliseconds
*/
void scheduler_update(long long int cur_time){

	//TODO: make this thread safe?

    //dlog_print(DLOG_ERROR, LOG_TAG, "[%s:%d] Updating scheduler with time %lli", __FILE__, __LINE__, cur_time);
    
//	if((int)(cur_time / 1000) % 5 == 0){
//	    print_schedule();
//	}

    for(int i = 0; i < scheduler_data.unitcount;){ //if unit is executed, it is also deleted so no need to increase i
        if(scheduler_data.arr[i].timestamp < cur_time){
            scheduler_execute_unit(&scheduler_data.arr[i]); //execute this unit
            scheduler_unit_index_remove(i); //remove the unit
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
    dlog_print(DLOG_INFO, LOG_TAG, "[%s:%d] Updating scheduler with time %llu, units remaining: %i", __FILE__, __LINE__, cur_time, scheduler_data.unitcount);
    scheduler_update((long long int) cur_time); //update scheduler

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






// int main(){
//     for(int i = 499; i >= 0; i--){
//         schedule_unit temp;
//         temp.timestamp = rand() % 2000;//rand()%101 + rand()%50;
//         temp.unit_id = scheduler_get_new_unit_id();
//         temp.unit_target_id = i % 10;
//         temp.unit_action_id = i%2;
//         //printf("Adding %i with timestamp: %llu \n", i, temp.timestamp);
//         scheduler_unit_add(&temp);

//     }


//     printf("--------------------------------------------------------------------------------\n"); 
//     for(int i = 0; i < 1500; i+=100){
//         scheduler_update(i);
//         printf("\n");
//     }

    
//     printf("--------------------------------------------------------------------------------\n");


//     //print_schedule();
//     printf("ID_Counter: %i\n", scheduler_data.id_counter);
//     printf("Unitcount: %i\n", scheduler_data.unitcount);
//     scheduler_finalize();
//     return 0;
// }
