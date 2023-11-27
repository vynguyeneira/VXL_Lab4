/*
 * button.c
 *
 *  Created on: Nov 15, 2023
 *      Author: Vy Nguyen
 */

#include "button.h"

/*
 Declare variables for handling vibration suppression, signal processing, and
 button handling in two modes (normal press and long press
*/

int keyReg0[NUM_OF_BUTTONS] = {NORMAL_STATE};
int keyReg1[NUM_OF_BUTTONS] = {NORMAL_STATE};
int keyReg2[NUM_OF_BUTTONS] = {NORMAL_STATE};
int keyReg3[NUM_OF_BUTTONS] = {NORMAL_STATE};

/*
 Declare "flag" for each button
 */
int normal_press_flag[NUM_OF_BUTTONS] = {0};
int long_press_flag[NUM_OF_BUTTONS] = {0};

/*
 Declare cycle counters to determine the two possible
 events of the button
 */
int timeOutForKeyPress[NUM_OF_BUTTONS] = {0};

//--------------//

int isButtonPressed(int index)
{
	if(normal_press_flag[index] == 1)
	{
		normal_press_flag[index] = 0;
		return 1;
	}
	return 0;
}

//--------------//

void subKeyProcess(int index)
{
	normal_press_flag[index] = 1;
}

//-------------//

void getKeyInput()
{
	for (int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		// Handling vibration suppression
		keyReg0[i] = keyReg1[i];
		keyReg1[i] = keyReg2[i];

		//Read signals from the buttons
		if (i == 0)
		{
			keyReg2[i] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
		}

		//Handling signals
		if ((keyReg1[i] == keyReg0[i]) && (keyReg1[i] == keyReg2[i]))
		{
			if(keyReg3[i] != keyReg2[i])
			{
				keyReg3[i] = keyReg2[i];
				if(keyReg2[i] == PRESSED_STATE)
				{
					subKeyProcess(i);
					if (long_press_flag[i] == 0)
					{
						timeOutForKeyPress[i] = 2000 / TIME_CYCLE;
					}
					else
					{
						timeOutForKeyPress[i] = 1000 / TIME_CYCLE;
					}
				}
			}

			else
			{
				timeOutForKeyPress[i]--;
				if(timeOutForKeyPress[i] == 0)
				{
					keyReg3[i] = NORMAL_STATE;
					long_press_flag[i] = 1;
				}
			}
		}

		else
		{
			long_press_flag[i] = 0;
		}
	}
}

