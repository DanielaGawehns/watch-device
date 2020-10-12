/*
 * activityrecog.cpp
 *
 *  Created on: May 20, 2020
 *      Author: frederick
 */
#include <sys/time.h>
#include <activityrecog.h>

void setHandle(activity_h newHandle){
	handle = newHandle;
}

activity_h getHandle(){
	return handle;
}


void setIsAccuracy(bool newAccurate){
	isAccurate = newAccurate;
}

bool getIsAccurate(){
	return isAccurate;
}

void setActivityStates(activity_type_e newState){
	currentState = newState;
}

activity_type_e getActivityStates(){
	return currentState;
}


void setActivityAccuracy(activity_accuracy_e newAccuracy){
	activity_accuracy = newAccuracy;
}

activity_accuracy_e getActivityAccuracy(){
	return activity_accuracy;
}

sensor_event_s *createEvent(activity_accuracy_e accuracy, double timestamp, a_info activity_info,
		activity_type_e activity){
	sensor_event_s* newEvent;
	float values[16] = {activity_info.run_accuracy, activity_info.walk_accuracy, activity_info.stationary_accuracy,
			activity_info.vehicle_accuracy, activity};

	newEvent->accuracy = accuracy;
	newEvent->timestamp = timestamp;
	newEvent->value_count = 5;

	for (int i = 0;  i < 4; ++ i) {
		newEvent->values[i] = values[i];
	}
	dlog_print(DLOG_INFO, LOG_TAG, "Created an new event thing");

	return newEvent;

}

void activity_callback(activity_type_e activity, const activity_data_h data, double timestamp, activity_error_e error, a_info activity_info){
	activity_accuracy_e accuracy;
	int result;
	activity_info.activity_type = activity;
	if(error != ACTIVITY_ERROR_NONE){
		dlog_print(DLOG_DEBUG, LOG_TAG, "An error has occured with activity %d", activity );
	}

	if(activity == ACTIVITY_STATIONARY){
		result = activity_get_accuracy(data, &accuracy);
		activity_info.stationary_accuracy = accuracy;
	}

	switch (activity) {
		case ACTIVITY_RUN:
			result = activity_get_accuracy(data, &accuracy);
			activity_info.run_accuracy = accuracy;
			break;
		case ACTIVITY_WALK:
			result = activity_get_accuracy(data, &accuracy);
			activity_info.walk_accuracy = accuracy;
			break;
		case ACTIVITY_STATIONARY:
			result = activity_get_accuracy(data, &accuracy);
			activity_info.stationary_accuracy = accuracy;
			break;
		case ACTIVITY_IN_VEHICLE:
			result = activity_get_accuracy(data, &accuracy);
			activity_info.vehicle_accuracy = accuracy;
			break;
		default:
			dlog_print(DLOG_DEBUG, LOG_TAG, "Could not detect the activity");

			break;
	}

	//sensor_event_s *ev = createEvent(accuracy, timestamp, activity_info, activity);

	long long time_millis;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	time_millis = tv.tv_sec * 1000LL + tv.tv_usec/1000LL;
	double thedata[5];
	thedata[0] = activity_info.run_accuracy;
	thedata[1] = activity_info.walk_accuracy;
	thedata[2] = activity_info.stationary_accuracy;
	thedata[3] = activity_info.vehicle_accuracy;
	thedata[4] = activity;
	dlog_print(DLOG_INFO, LOG_TAG, "Send recog data is sent to the database");
	database_record_data("actreg", time_millis, 5, thedata);
	dlog_print(DLOG_INFO, LOG_TAG, "Activity recog data is sent to the database");


}



/*static activity_h* InitializeActivity(activity_type_e type){
	activity_h handle = NULL;
	bool supported = false;
	dlog_print(DLOG_DEBUG, LOG_TAG, "The current activity is: %d", type);

	if(activity_is_supported(type, &supported) != ACTIVITY_ERROR_NONE || !supported){
		dlog_print(DLOG_ERROR, LOG_TAG, "Activity not supported on current device: %d", type);
		return NULL;
	}

	if(activity_create(&handle) != ACTIVITY_ERROR_NONE){
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to initialize activity handle: %d", type);
		return NULL;

	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "The current handle is: %d", handle);


	if(activity_start_recognition(handle, type, activity_callback, NULL) != ACTIVITY_ERROR_NONE){
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to start the activity recognition of activity: %d", type);
		activity_release(handle);
		return NULL;
	}



	return handle;
}*/



activity_h _initialize_recog_activity(activity_type_e type){
	activity_h handle = NULL;
	bool supported = false;

	if(activity_is_supported(type, &supported) != ACTIVITY_ERROR_NONE || !supported){
		dlog_print(DLOG_ERROR, LOG_TAG, "Activity not supported on current device: %d", type);
		return -1;
	}

	if(activity_create(&handle) != ACTIVITY_ERROR_NONE){
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to initialize activity handle: %d", type);
		return -1;

	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "Initializing activity %d was succesful", type);

	return handle;
}


int GetActivity(){
	/*GetActivityStats(ACTIVITY_STATIONARY);
	GetActivityStats(ACTIVITY_WALK);
	GetActivityStats(ACTIVITY_RUN);
	GetActivityStats(ACTIVITY_IN_VEHICLE);


	for (int var = 1; var < 4; ++var) {
		bool supported = false;
		activity_is_supported(var, &supported);
		if(!supported){
			dlog_print(DLOG_DEBUG, LOG_TAG, "Activity recognition for activity %d is not supported", var);

		}
	}

	char* file_path;
	char temp[115];
	sprintf(temp, "Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n",
			all_activities[0].act_type, accuracies[0],
			all_activities[1].act_type, accuracies[1],
			all_activities[2].act_type, accuracies[2],
			all_activities[3].act_type, accuracies[3]
	);
	file_path = get_write_filepath("test.txt");
	dlog_print(DLOG_DEBUG, LOG_TAG, "Buffer: %d", all_activities);
	write_file(file_path, temp);


	return all_activities[2].act_acc;

	s_info.stationary_handle = InitializeActivity(ACTIVITY_STATIONARY);
	s_info.walk_handle = InitializeActivity(ACTIVITY_WALK);
	s_info.run_handle = InitializeActivity(ACTIVITY_RUN);
	s_info.vehicle_handle = InitializeActivity(ACTIVITY_IN_VEHICLE);

	char* file_path;
		char temp[115];
		sprintf(temp, "Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n Activity: %d, Accuracy: %d \n",
				ACTIVITY_STATIONARY, s_info.stationary_accuracy,
				ACTIVITY_RUN, s_info.run_accuracy,
				ACTIVITY_WALK, s_info.walk_accuracy,
				ACTIVITY_IN_VEHICLE, s_info.vehicle_accuracy
		);
		file_path = get_write_filepath("test.txt");
//		dlog_print(DLOG_DEBUG, LOG_TAG, "Buffer: %d", all_activities);
		write_file(file_path, temp);


	//	return all_activities[2].act_acc;
		return 0; */
	}

