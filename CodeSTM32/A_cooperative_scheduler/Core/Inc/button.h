/*
 * button.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Vy Nguyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "scheduler.h"

#define NORMAL_STATE	SET
#define PRESSED_STATE	RESET

#define NUM_OF_BUTTONS	1

int isButtonPressed(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */
