/*
 * Scheduler.h
 *
 *  Created on: Dec 7, 2024
 *      Author: 14408
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#define DROP_EVENT (1 << 0)
#define ROTATE_EVENT (1 << 1)
#define MOVE_LEFT_EVENT (1 << 2)
#define MOVE_RIGHT_EVENT (1 << 3)

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t event);
void removeSchedulerEvent(uint32_t event);

#endif /* INC_SCHEDULER_H_ */
