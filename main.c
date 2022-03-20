/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Travis
 * @brief          : Interface a keypad with purely address manipulation
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
//delays the key presses
void delay() {
	for (uint32_t i=0; i>300000; i++);
}

int main(void)
{
	uint32_t volatile *const pGPIODModeReg = (uint32_t *)(0x40020C00);
	uint32_t volatile *const pInputDataReg = (uint32_t *)(0x40020C00 + 0x10);
	uint32_t volatile *const pOutPutDataReg = (uint32_t *)(0x40020C00 + 0x14);
	uint32_t volatile *const pClockCtrlReg = (uint32_t *)(0x40023800 + 0x30);
	uint32_t volatile *const pPullupDownReg = (uint32_t *)(0x40020C00 + 0x0C);
    /* Loop forever */

	//No key is pressed then C1, C2, C3, C4 are high

	//ex if key pressed in C2 then 1011 since C2 will be at ground state
	// r1 is low and C2 is low therefore button in row 1 column 2 was pressed

	//enable internal clock GPIOD peripheral
	*pClockCtrlReg |= (1 << 3);

	// output (rows) PD0, PD1,PD2,PD3
	//r1, r2, r3, r4
	*pGPIODModeReg &= ~(0xFF); // clears bits
	*pGPIODModeReg |= 0x55; 	//sets bits

	//input (columns) PD8, PD9, PD10, PD11
	//c1, c2, c3, c4
	*pGPIODModeReg &= ~(0xFF << 16); // clears bits

	// enable pullup resistor
	*pPullupDownReg &= ~(0xFF << 16); // clears bits
	*pPullupDownReg |= (0x55 << 16); // sets bits 01010101 bits 16 to 23

	while (1) {
		//make Row GPIOs HIGH
		*pOutPutDataReg |= 0x0f;

		// make PD0 low
		*pOutPutDataReg &= ~(1);


		//Make R1 Low state 0111
		//check c1 low yes -> 200ms delay -> key 1
		if (!(*pInputDataReg & (1 << 8))) {
			delay();
			printf("1/n");
		}

		//check c2 low yes -> 200ms delay -> key 2
		if (!(*pInputDataReg & (1 << 9))) {
			delay();
			printf("2/n");
		}


		//check c3 low yes -> 200ms delay -> key 3
		if (!(*pInputDataReg & (1 << 10))) {
			delay();
			printf("3/n");
		}

		//check c4 low yes -> 200ms delay -> key 4
		if (!(*pInputDataReg & (1 << 11))) {
			delay();
			printf("A/n");
		}

		//then make r2  scan columns rows 1011 repeat for 1101 and 1110
		*pOutPutDataReg |= 0x0f;
		*pOutPutDataReg &= ~(1 << 1);

		if (!(*pInputDataReg & (1 << 8))) {
			delay();
			printf("4/n");
		}

			//check c2 low yes -> 200ms delay -> key 2
		if (!(*pInputDataReg & (1 << 9))) {
			delay();
			printf("5/n");
		}


			//check c3 low yes -> 200ms delay -> key 3
		if (!(*pInputDataReg & (1 << 10))) {
			delay();
			printf("6/n");
		}

			//check c4 low yes -> 200ms delay -> key 4
		if (!(*pInputDataReg & (1 << 11))) {
			delay();
			printf("B/n");
		}

				//then make r2  scan columns rows 1011 repeat for 1101 and 1110
		*pOutPutDataReg |= 0x0f;
		*pOutPutDataReg &= ~(1 << 2);

		if (!(*pInputDataReg & (1 << 8))) {
			delay();
			printf("7/n");
		}

		//check c2 low yes -> 200ms delay -> key 2
		if (!(*pInputDataReg & (1 << 9))) {
			delay();
			printf("8/n");
		}


		//check c3 low yes -> 200ms delay -> key 3
		if (!(*pInputDataReg & (1 << 10))) {
			delay();
			printf("9/n");
		}

		//check c4 low yes -> 200ms delay -> key 4
		if (!(*pInputDataReg & (1 << 11))) {
			delay();
			printf("C/n");
		}

		*pOutPutDataReg |= 0x0f;
		*pOutPutDataReg &= ~(1 << 3);

		if (!(*pInputDataReg & (1 << 8))) {
			delay();
			printf("*/n");
		}

		//check c2 low yes -> 200ms delay -> key 2
		if (!(*pInputDataReg & (1 << 9))) {
			delay();
			printf("0/n");
		}


		//check c3 low yes -> 200ms delay -> key 3
		if (!(*pInputDataReg & (1 << 10))) {
			delay();
			printf("#/n");
		}

		//check c4 low yes -> 200ms delay -> key 4
		if (!(*pInputDataReg & (1 << 11))) {
			delay();
			printf("D/n");
		}
	}
}
