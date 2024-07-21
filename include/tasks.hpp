#ifndef TASKS_H
#define TASKS_H

#include "header.hpp"
#include "screen.hpp"
#include "servers.hpp"

extern Scheduler ts;

extern Task screen_update_task;
extern Task vars_update_task;
extern Task wifi_tasks;
extern Task connect_wifi_task;

#endif //TASKS_H