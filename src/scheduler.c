
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"

#define SCHEDULESIZEINCREASE 200 //Data increase per time the scheduler array is too small

//for debgging purposes
const char *sensor_strings[50] = {
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
    "NOT ADDED"
};

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
    .active = false
};

void scheduler_reset(){ //resets scheduler to default
    scheduler_data.id_counter = 1;
    scheduler_data.unitcount = 0;
    scheduler_data.size = 0;
    scheduler_data.active = false;
    free(scheduler_data.arr);
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


void scheduler_increase_size(){
    printf("Increasing size\n");
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
        if(scheduler_data.arr[i].unit_id == 0)
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

 void scheduler_execute_unit(schedule_unit * unit){
     //TODO: link this to sensor
     printf("Executing unit with Timestamp: %llu      ID: %i     Target:%s     Action:%i \n", unit->timestamp, unit->unit_id, sensor_strings[ unit->unit_target_id],  unit->unit_action_id);
    
 }


void print_schedule(){
    for(int i =0; i < scheduler_data.unitcount; i++){
        printf("%i - Timestamp: %llu      ID: %i     Target:%s     Action:%i \n", i, scheduler_data.arr[i].timestamp, scheduler_data.arr[i].unit_id, sensor_strings[scheduler_data.arr[i].unit_target_id], scheduler_data.arr[i].unit_action_id);
    }
}

void scheduler_update(long long int cur_time){
    for(int i = 0; i < scheduler_data.unitcount;){ //if unit is executed, it is also deleted so no need to increase i
        if(scheduler_data.arr[i].timestamp < cur_time){
            scheduler_execute_unit(&scheduler_data.arr[i]); //execute this unit
            scheduler_unit_index_remove(i); //remove the unit
        }else{ //since it is sorted -> stop when first not-to-be-executed unit is encountered
            break;
        }
    }

}






int main(){
    for(int i = 499; i >= 0; i--){
        schedule_unit temp;
        temp.timestamp = rand() % 2000;//rand()%101 + rand()%50;
        temp.unit_id = scheduler_get_new_unit_id();
        temp.unit_target_id = i % 10;
        temp.unit_action_id = i%2;
        //printf("Adding %i with timestamp: %llu \n", i, temp.timestamp);
        scheduler_unit_add(&temp);

    }


    printf("--------------------------------------------------------------------------------\n"); 
    for(int i = 0; i < 1500; i+=100){
        scheduler_update(i);
        printf("\n");
    }

    
    printf("--------------------------------------------------------------------------------\n");


    //print_schedule();
    printf("ID_Counter: %i\n", scheduler_data.id_counter);
    printf("Unitcount: %i\n", scheduler_data.unitcount);
    scheduler_finalize();
    return 0;
}