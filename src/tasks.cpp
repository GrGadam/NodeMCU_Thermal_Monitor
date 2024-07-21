#include "tasks.h"

Scheduler ts;

Task screen_update_task(1000, TASK_FOREVER, &update_screen);
Task vars_update_task(1000, TASK_FOREVER, &update_vars);
Task wifi_tasks(1000, TASK_ONCE, &handle_wifi_tasks);
Task connect_wifi_task(1000, TASK_ONCE, &connect_to_wifi);