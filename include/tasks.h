#ifndef NODEMCU_THERMAL_MONITOR_TASKS_H
#define NODEMCU_THERMAL_MONITOR_TASKS_H

#include "TaskScheduler.h"
#include "screen.h"
#include "servers.h"

extern Scheduler ts;

extern Task screen_update_task;
extern Task vars_update_task;
extern Task wifi_tasks;
extern Task connect_wifi_task;

#endif // NODEMCU_THERMAL_MONITOR_TASKS_H