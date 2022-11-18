#include <stdint.h>
#include "stm32f10x.h"
#include "system_stm32f10x.h"

void delay_1ms (){
	uint32_t check=0;
	SysTick->LOAD = 999;
	SysTick->CTRL = 1;
	check = SysTick->CTRL & (1<<16);
	while(!check){
		check = SysTick->CTRL & (1<<16);
	}
	return;
}

void SysTick_Handler(){
	GPIOB->ODR ^= (1<<12);
	return;
}


int main(void)
{
	RCC->APB2ENR = 0x08;
		//PB12
	GPIOB->ODR |= (1<<12);

	//exercicio 1
    /*while(1){
    	for(int i=0; i<50; i++){
    		delay_1ms();
    	}
    	GPIOB->ODR ^= (1<<12);

    }*/

	//exercicio 3
	/*SysTick->LOAD = 999999;
	SysTick->CTRL = 0x3;
	while(1){

	}*/

	//exercicio 4
	uint8_t alto=3; //valores dinamicos para as alternativas A, B e C
	uint8_t baixo=1;
	uint32_t check=0;
	uint8_t flip= 250;
	SysTick->CTRL = 0x3;
	SysTick->LOAD = (flip*alto)-1;
	while(1){
		check = GPIOB->ODR & (1<<12);
		if(check){
			SysTick->LOAD = (flip*baixo)-1;
		}
		if(!check){
			SysTick->LOAD = (flip*alto)-1;
		}

	}
}


/////começa aqui

#include <stdint.h>;
#include "stm32f10x.h"
#include "system_stm32f10x.h"

void abrirMotor(){
	uint8_t alto=10; //valores dinamicos para as alternativas A, B e C
	uint8_t baixo=10;
	uint32_t check=0;
	uint32_t frequencia = 50; //freq em hertz
	uint32_t flip = 1000/frequencia; //tempo em ms para o flip
	SysTick->CTRL = 0x3;
	SysTick->LOAD = (flip*alto)-1;
	while(1){
		check = GPIOB->ODR & (1<<12);
		if(check){
			SysTick->LOAD = (flip*baixo)-1;
		}
		if(!check){
			SysTick->LOAD = (flip*alto)-1;
		}
	}



}

void fecharMotor(){
	uint8_t alto=1; //valores dinamicos para as alternativas A, B e C
	uint8_t baixo=19;
	uint32_t check=0;
	uint32_t frequencia = 50; //freq em hertz
	uint32_t flip = 1000/frequencia; //tempo em ms para o flip
	SysTick->CTRL = 0x3;
	SysTick->LOAD = (flip*alto)-1;
	while(1){
		check = GPIOB->ODR & (1<<12);
		if(check){
			SysTick->LOAD = (flip*baixo)-1;
		}
		if(!check){
			SysTick->LOAD = (flip*alto)-1;
		}


	}

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

int main(void){
	RCC->APB2ENR = 0x0C;
	GPIOB->CRH = 0x44434444; //PB12
	GPIOB->ODR |= (1<<12);

	abrirMotor();
}
