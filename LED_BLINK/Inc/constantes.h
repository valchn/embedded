#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef enum
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE,
  GPIOF,
  GPIOG,
  GPIOH,
  GPIOI
} enumGPIOx;

typedef enum
{
	PinGPIO_0,
	PinGPIO_1,
	PinGPIO_2,
	PinGPIO_3,
	PinGPIO_4,
	PinGPIO_5,
	PinGPIO_6,
	PinGPIO_7,
	PinGPIO_8,
	PinGPIO_9,
	PinGPIO_10,
	PinGPIO_11,
	PinGPIO_12,
	PinGPIO_13,
	PinGPIO_14,
	PinGPIO_15
} enumGPIOPin;

typedef enum
{
	Active,
	Desactive,
	Inversion
} enumEtatPinOut;

#endif
