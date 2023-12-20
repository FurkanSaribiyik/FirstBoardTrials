/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
#define Gpio_Clock_Enable ((0x40023800)+(0x30))
#define Gpio_D_Mode_BaseAddr (0x40020C00)
#define Gpio_D_OutputData_Reg ((0x40020C00)+(0x14))
#define Gpio_A_Mode_BaseAddr (0x40020000)
#define Gpio_A_InputData_Reg ((0x40020000)+(0x10))
#define Gpio_A_PupdData_Reg ((0x40020000)+(0x0C))

void turnoffall_LEDS(void);
bool isButtonPushed(volatile bool *,volatile bool *,volatile const uint32_t*);
int main(void)
{
	volatile uint32_t * const pClockEnReg= (uint32_t *) Gpio_Clock_Enable;
	volatile uint32_t * const pGpio_D_ModeReg= (uint32_t *) Gpio_D_Mode_BaseAddr;
	volatile uint32_t * const pGpio_D_OutputReg= (uint32_t *) Gpio_D_OutputData_Reg;
	*pClockEnReg|=(1<<3);		//Enabling GpioD clock
	*pGpio_D_ModeReg&=~(3<<24); //Clearing the bits for 12th pin  1111 1100 1111 1111 GREEN LED
	*pGpio_D_ModeReg|= (1<<24);	//Setting bit 24 (PD12) for output GREEN LED
	*pGpio_D_ModeReg|= (1<<26);	//Setting bit 26 (PD13) for output ORANGE LED
	*pGpio_D_ModeReg|= (1<<28);	//Setting bit 28 (PD14)for output RED LED
	*pGpio_D_ModeReg|= (1<<30);	//Setting bit 30 (PD15)for output BLUE LED

	*pClockEnReg|=(1<<0);	//Enabling GpioA clock
	volatile uint32_t* const pGpio_A_ModeReg=(uint32_t *) Gpio_A_Mode_BaseAddr;
	volatile uint32_t* const pGpio_A_InputReg= (uint32_t *) Gpio_A_InputData_Reg;
	volatile uint32_t* const pGpio_A_PupdReg= (uint32_t *) Gpio_A_PupdData_Reg;
	*pGpio_A_PupdReg|=(2<<0);	//Setting GpioA0 as default pull down
	*pGpio_A_ModeReg&=~(3<<0); //Clearing bits 0 and 1 for GPIO_A0 and by default it is in input mode
	bool volatile toggle=FALSE;
	bool volatile status=FALSE;
	while(1)
		{
		status=FALSE;
			if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
				{
				status=TRUE;
					while(toggle)	//if user button is pressed temp=1 if user button is not pressed temp=0
					{
							if(toggle)
							{
								*pGpio_D_OutputReg|=(1<<12);	//Turning on GREEN LED
								for(int i=0;i<=100000;i++)
								{
									if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
									{
										break;
									}
								}
							}
							else
							{
								break;
							}
							if(toggle)
							{
								*pGpio_D_OutputReg|=(1<<13);	//Turning on ORANGE LED
								for(int i=0;i<=100000;i++)
								{
									if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
									{
										break;
									}
								}
							}
							else
							{
								break;
							}
							if(toggle)
							{
								*pGpio_D_OutputReg|=(1<<14);	//Turning on RED LED
								for(int i=0;i<=100000;i++)
								{
									if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
									{
										break;
									}
								}
							}
							else
							{
								break;
							}
							if(toggle)
							{
								*pGpio_D_OutputReg|=(1<<15);	//Turning on BLUE LED
								for(int i=0;i<=100000;i++)
								{
									if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
									{
										break;
									}
								}
							}
							else
							{
								break;
							}
							*pGpio_D_OutputReg&=~(1<<12);	//Turning off GREEN LED
							for(int i=0;i<=100000;i++)
							{
								if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
								{
									break;
								}
							}
							*pGpio_D_OutputReg&=~(1<<13);	//Turning off ORANGE LED
							for(int i=0;i<=100000;i++)
							{
								if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
								{
									break;
								}
							}
							*pGpio_D_OutputReg&=~(1<<14);	//Turning off RED LED
							for(int i=0;i<=100000;i++)
							{
								if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
								{
									break;
								}
							}
							*pGpio_D_OutputReg&=~(1<<15);	//Turning off BLUE LED
							for(int i=0;i<=100000;i++)
							{
								if(isButtonPushed(&toggle,&status,pGpio_A_InputReg))
								{
									break;
								}
							}
						}
				}


		}

}


bool isButtonPushed(volatile bool *toggle,volatile bool * status,volatile const uint32_t* pGpio_A_InputReg)
{
	volatile uint32_t * const pGpio_D_OutputReg = (uint32_t *) Gpio_D_OutputData_Reg;
	uint32_t volatile temp=*pGpio_A_InputReg;
	temp&=0x1;
	uint32_t volatile tempOutput=*pGpio_D_OutputReg;
	if(temp)
	{
		if(*status==TRUE)		// if the status is active
		{
			*pGpio_D_OutputReg|=(1<<15); 		//Turning on BLUE LED indicating that the system is ready
			for(int i=0;i<=500000;i++)//software delay if the button is pushed
			{
			}
			*pGpio_D_OutputReg&=~(1<<15); 		//Turning off the BLUE LED/ Button was held for too long
			temp=*pGpio_A_InputReg;
			temp&=0x1;

			if(temp)		//if the button is pressed for too long the order will be cancelled indicated with a red LED
			{
				while(temp)
				{
					temp=*pGpio_A_InputReg;
					temp&=0x1;
					*pGpio_D_OutputReg|=(1<<14);	//Turning on RED LED
					for(int i=0;i<=250000;i++)
					{
					}
					*pGpio_D_OutputReg&=~(1<<14);	//Turning off RED LED
					for(int i=0;i<=250000;i++)
					{
					}
				}
				*pGpio_D_OutputReg=tempOutput;
				return FALSE;
			}
			else
			{
				*toggle=FALSE;
				turnoffall_LEDS();
				return TRUE;
			}

		}



		else		// if the status is inactive
		{
			*pGpio_D_OutputReg|=(1<<15); 		//Turning on BLUE LED indicating that the system is ready
			for(int i=0;i<=500000;i++)//software delay if the button is pushed
			{
			}
			*pGpio_D_OutputReg&=~(1<<15); 		//Turning off the BLUE LED/ Button was held for too long
			temp=*pGpio_A_InputReg;
			temp&=0x1;
			if(temp)		//if the button is pressed for too long the order will be cancelled indicated with a red LED
			{
				while(temp)
				{
					temp=*pGpio_A_InputReg;
					temp&=0x1;
					*pGpio_D_OutputReg|=(1<<14);	//Turning on RED LED
					for(int i=0;i<=250000;i++)
					{
					}
					*pGpio_D_OutputReg&=~(1<<14);	//Turning off RED LED
					for(int i=0;i<=250000;i++)
					{
					}
				}
				*toggle=FALSE;
				*status=FALSE;
				return FALSE;
			}
			else
			{
				*toggle=TRUE;
				return TRUE;
			}
		}


	}
	else
	{
		return FALSE;
	}

}


void turnoffall_LEDS(void)
{
	uint32_t volatile *pGpio_D_OutputReg= (uint32_t *) Gpio_D_OutputData_Reg;
	*pGpio_D_OutputReg&=~(1<<12);
	*pGpio_D_OutputReg&=~(1<<13);
	*pGpio_D_OutputReg&=~(1<<14);
	*pGpio_D_OutputReg&=~(1<<15);
}
