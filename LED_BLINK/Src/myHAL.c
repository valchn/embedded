/*
 * myHAL.c
 *
 *  Created on: May 7, 2025
 *      Author: valen
 */

#include "myHAL.h"

bool bSetPinOut(enumGPIOx p_eGPIOx, enumGPIOPin p_eGPIOPin, enumEtatPinOut p_eEtatSortie)
{
	volatile uint32_t *l_uRccAhb1enr = (volatile uint32_t *) 0x40023830;
	volatile uint32_t *l_uGpioxModer = NULL;
	volatile uint32_t *l_uGpioxOdr = NULL;

	int l_iPositionBitsGpioModer = p_eGPIOPin*2;

	switch(p_eGPIOx)
	{
		case GPIOA:
			// On active la clock sur le GPIOA
			*l_uRccAhb1enr |= (1 << 0);

			// On pointe sur le registre GPIOA_MODER
			l_uGpioxModer = (volatile uint32_t *) 0x40020000;

			// On pointe sur le registre GPIOA_ODR
			l_uGpioxOdr = (volatile uint32_t *) 0x40020014;
			break;

		case GPIOB:
			*l_uRccAhb1enr |= (0b01 << 1);
			l_uGpioxModer = (volatile uint32_t *) 0x40020400;
			l_uGpioxOdr = (volatile uint32_t *) 0x40020414;
			break;

		case GPIOC:
			*l_uRccAhb1enr |= (0b01 << 2);
			l_uGpioxModer = (volatile uint32_t *) 0x40020800;
			l_uGpioxOdr = (volatile uint32_t *) 0x40020814;
			break;

		case GPIOD:
			*l_uRccAhb1enr |= (0b01 << 3);
			l_uGpioxModer = (volatile uint32_t *) 0x40020C00;
			l_uGpioxOdr = (volatile uint32_t *) 0x40020C14;
			break;

		case GPIOE:
			*l_uRccAhb1enr |= (0b01 << 4);
			l_uGpioxModer = (volatile uint32_t *) 0x40021000;
			l_uGpioxOdr = (volatile uint32_t *) 0x40021014;
			break;

		case GPIOF:
			*l_uRccAhb1enr |= (0b01 << 5);
			l_uGpioxModer = (volatile uint32_t *) 0x40021400;
			l_uGpioxOdr = (volatile uint32_t *) 0x40021414;
			break;

		case GPIOG:
			*l_uRccAhb1enr |= (0b01 << 6);
			l_uGpioxModer = (volatile uint32_t *) 0x40021800;
			l_uGpioxOdr = (volatile uint32_t *) 0x40021814;
			break;

		case GPIOH:
			*l_uRccAhb1enr |= (0b01 << 7);
			l_uGpioxModer = (volatile uint32_t *) 0x40021C00;
			l_uGpioxOdr = (volatile uint32_t *) 0x40021C14;
			break;

		case GPIOI:
			*l_uRccAhb1enr |= (0b01 << 8);
			l_uGpioxModer = (volatile uint32_t *) 0x40022000;
			l_uGpioxOdr = (volatile uint32_t *) 0x40022014;
			break;

		default:
			return false;
	}

	// On passe le pin en mode sortie
	*l_uGpioxModer &= ~(0b11 << l_iPositionBitsGpioModer);
	*l_uGpioxModer |= (0b01 << l_iPositionBitsGpioModer);

	// On active ou pas la sortie
	if(p_eEtatSortie == Active)
	{
		*l_uGpioxOdr |= (0b01 << p_eGPIOPin);
	}
	else if(p_eEtatSortie == Desactive)
	{
		*l_uGpioxOdr &= ~(0b01 << p_eGPIOPin);
	}
	else if(p_eEtatSortie == Inversion)
	{
		*l_uGpioxOdr ^= (0b01 << p_eGPIOPin);
	}
	else
	{
		return false;
	}

	return true;

}


