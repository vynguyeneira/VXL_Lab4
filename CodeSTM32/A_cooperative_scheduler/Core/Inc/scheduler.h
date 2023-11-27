/*
 * scheduler.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Vy Nguyen
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define SCH_MAX_TASKS		40

extern int TIME_CYCLE;

typedef struct
{
// Pointer to the task (must be a ’ void ( void ) ’ function )
void ( * pTask ) ( void ) ;
// Delay ( ticks ) until the function will ( next ) be run
uint32_t Delay ;
// Interval ( ticks ) between subsequent runs .
uint32_t Period ;
// Incremented (by scheduler) when task is due to execute
uint8_t RunMe;
//This is a hint to solve the question below .
uint32_t TaskID ;
} sTask ;

uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_int(void);
uint32_t SCH_Add_Task (void (*pFunction)(),
			uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);


#endif /* INC_SCHEDULER_H_ */
