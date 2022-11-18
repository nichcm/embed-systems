#include <stdint.h>
#include "stm32f10x.h"
#include "system_stm32f10x.h"

void SysTick_Handler(){
	GPIOB->ODR &= (~(1<<12));
	return;
}

void delay_1ms (){
	uint32_t check=0;
	SysTick->LOAD = 999;
	SysTick->CTRL = 1;
	check = SysTick->CTRL;
	while(!check){
		check = SysTick->CTRL & (1<<16);
	}
	return;
}


void delay(uint32_t ms){
	uint32_t i,j;
	for(i=0; i<ms; i++){
		for(j=0; j<880; j++){}
	}
}

uint32_t get_adc (void)
{
	uint32_t result;

	ADC1->SQR3 = 0x01;
	ADC1->CR2 = 0x01;						// inicia o processo de conversao
	while((ADC1->SR & (1<<1)) == 0) { } 	// aguarda a conclusao do processo de conversao AD
	result = ADC1->DR;						// faz a leitura do registrador do AD
	return result;
}

int main(void){
	RCC->APB2ENR = 0x0000020C;  //ADC1, GPIOA e B
	GPIOB->CRH = 0x44434444; //PB12
	GPIOA->CRL= 0x44444404; //PA1 entrada analogica
	GPIOA->CRH = 0x84444444; //PA15 entrada
	GPIOA->ODR = GPIOA->ODR | (1<<15);  // habilita o pull-up no PA10
	SysTick->CTRL = 0x3;
	ADC1->SMPR2 = (1<<3);

	int teclaA15=0;
	uint32_t check=0;

	while(1){
		teclaA15 = GPIOA->IDR & (1<<15);
		check = get_adc();

		if(!teclaA15 || check>800){
			GPIOB->ODR |= (1<<12);
			SysTick->LOAD = 9999;
			delay(500);
			/*for(int i=0;i<500;i++){
				delay_1ms();
			}*/
		}
	}
}
