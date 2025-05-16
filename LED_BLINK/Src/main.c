#include "myHAL.h"

// LD3 (orange) -> GPIO PD13
// LD4 (green) -> GPIO PD12
// LD5 (red) -> GPIO PD14
// LD6 (blue) -> GPIO PD15

void TIM6_DAC_IRQHandler(void)
{
	volatile uint32_t *l_uTim6_SR = (volatile uint32_t *) 0x40001010;
	*l_uTim6_SR &= ~(1 << 0);
	bSetPinOut(GPIOD, PinGPIO_15, Inversion);
}

int main(void)
{
	// Activer la clock du TIM6 sur le registre RCC_APB1ENR
	volatile uint32_t *l_uRccApb1enr = (volatile uint32_t *) 0x40023840;
	*l_uRccApb1enr |= (1 << 4);

	// Passer le autoreload à 5000 (TIMx_ARR)
	volatile uint32_t *l_uTim6_ARR = (volatile uint32_t *) 0x4000102C;
	*l_uTim6_ARR = (*l_uTim6_ARR & 0xFFFF0000) | (0x1388);

	// Passer le prescaler à 15999 (TIMx_PSC)
	volatile uint32_t *l_uTim6_PSC = (volatile uint32_t *) 0x40001028;
	*l_uTim6_PSC = (*l_uTim6_PSC & 0xFFFF0000) | (0x3E7F);

	// On récupère l'état du TIMER
	volatile uint32_t *l_uTim6_SR = (volatile uint32_t *) 0x40001010;

	// On met à jour le timer pour qu'il prenne en compte le prescale et l'auto reload
	volatile uint32_t *l_uTim6_EGR = (volatile uint32_t *) 0x40001014;
	*l_uTim6_EGR |= (1 << 0);

	// On active les interruptions sur le TIMER6
	volatile uint32_t *l_uTim6_DIER = (volatile uint32_t *) 0x4000100C;
	*l_uTim6_DIER |= (1 << 0);

	// On RAZ l'event
	*l_uTim6_SR &= ~(1 << 0);

	// On active l'interruption du TIM6 dans le NVIC
	volatile uint32_t *l_uNVIC_ISER1 = (volatile uint32_t *) 0xE000E104;
	*l_uNVIC_ISER1 |= (1 << 22);

	// Lancer le timer avec TIMx_CR1
	volatile uint32_t *l_uTim6_CR1 = (volatile uint32_t *) 0x40001000;
	*l_uTim6_CR1 |= (1 << 0);

	while (1)
	{

		// Temps que le TIMER n'est pas arrivé à échéance
		//while((*l_uTim6_SR & 0x01) == 0)
		//{
		//}

		//bSetPinOut(GPIOD, PinGPIO_15, true);

		// ON remet le flag à 0
		//*l_uTim6_SR &= ~(1 << 0);

		// Temps que le TIMER n'est pas arrivé à échéance
		//while((*l_uTim6_SR & 0x01) == 0)
		//{

		//}

		//bSetPinOut(GPIOD, PinGPIO_15, false);

		// ON remet le flag à 0
		//*l_uTim6_SR &= ~(1 << 0);

	}
}
