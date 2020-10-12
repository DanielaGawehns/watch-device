/*
 * activityrecog.h
 *
 *  Created on: May 20, 2020
 *      Author: frederick
 */

#ifndef ACTIVITYRECOG_H_
#define ACTIVITYRECOG_H_



#include <activity_recognition.h>
#include <sensor.h>
#include <sqlite_db.h>
#include <dlog.h>
#include <notification.h>
#include <gesture_recognition.h>
#include <unistd.h> // notice this! you need it!
#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "sensorbasicui"

/*typedef struct activities{
	activity_type_e act_type;
	activity_accuracy_e act_acc;
} activity_m;

int accuracies[4];
struct activities all_activities[4]; */
typedef struct act_info {
	activity_h* stationary_handle;
	activity_h* walk_handle;
	activity_h* run_handle;
	activity_h* vehicle_handle;
	activity_type_e activity_type;

	activity_accuracy_e stationary_accuracy;
	activity_accuracy_e walk_accuracy;
	activity_accuracy_e run_accuracy;
	activity_accuracy_e vehicle_accuracy;
} a_info;
int GetActivity();
//static activity_h* InitializeActivity(activity_type_e activity);
// static void _initialize_activity_recog(void);
activity_h _initialize_recog_activity(activity_type_e type);
activity_type_e currentState;

bool isAccurate;
activity_accuracy_e activity_accuracy;


void activity_callback(activity_type_e activity, const activity_data_h data, double timestamp, activity_error_e error, a_info activity_info);


sensor_event_s *createEvent(activity_accuracy_e accuracy, double timestamp, a_info activity_info,
		activity_type_e activity);

activity_h handle;
void setHandle(activity_h newHandle);

activity_h getHandle();

void setIsAccuracy(bool newAccurate);
bool getIsAccurate();

void setActivityStates(activity_type_e newState);

activity_type_e getActivityStates();


void setActivityAccuracy(activity_accuracy_e newAccuracy);

activity_accuracy_e getActivityAccuracy();


#endif /* ACTIVITYRECOG_H_ */
