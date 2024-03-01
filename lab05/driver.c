/******************************************
#
# Anindita Deb, Summer 2022
# CPE 3000 Lab05
#
# Description: I will create a project that will control the green
# LED (LD2) on the Nucleo board when pressing down on the user input
# button
#
# ==Usage==
#
#-LEDS must initially be off
#-When user input button is pushed down the LED must turn on
#-When user input button is released, the LED must turn off
#
******************************************/

#include "stm32l476xx.h" //these are the files that have been provided and imported
#include "core_cm4.h"

//Define your function prototypes here.
void LED_Init(void);		//naming LED initial state function
void BUTTON_Init(void);		//namimg the button's inital state function
void LED_ON(void);			//naming LED ON function
void LED_OFF(void);			//naming LED OFF function
uint32_t mask;				//define mask variable
uint32_t input;				//define input variable


int main(void){

//Write code here
	LED_Init(); 	//calling the initialized function
	BUTTON_Init();  //calling the button function
	LED_OFF(); 		//calling the off function
	//LED will be off when initally reset
	//LED (L2) will only turn on after user input button is pressed

	while(1){
		mask = 1UL<<13; //reading the user input button's pin PC13
		input = (GPIOC ->IDR&mask) == mask;

		if(input == 0){ //input=0 means user button not pressed
			LED_OFF(); //input is a LOW value, the LED must be off
		}
		else{ //input=1 means user button is pressed
			LED_ON(); //input is a HIGH value, the LED must be on
		}
	} //continuous while-loop
} //END main


//Implement the function protoypes here.

void LED_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enables the clock for port A

	GPIOA->MODER &= ~(3U<<(2*5)); //clear mode bits of 2*Pin 5
	GPIOA->MODER |=1U<<(2*5); //set mode to output

	GPIOA->OTYPER &= ~(1U<<(5)); //push-pull output type selected

	GPIOA->PUPDR &= ~(3U<<(2*5)); //output defined as no pull up, no pull down (00)
}

void BUTTON_Init(void){ 	//initalizing the user input button (B1 on the STM32 board)
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //Enables the clock for port C

	GPIOC->MODER &= ~(3U<<(2*13)); //clear mode bits of pin13 and use as input

	GPIOC->PUPDR &= ~(3U<<(2*13)); //output
	GPIOC->PUPDR |= (2UL<<(2*13)); //defined as pull down (10)

}

void LED_ON(void){
	GPIOA->ODR &= 0U<<5; //assigns a specific output value to pin 5 is 0
	// GPIOA->ODR &= ~GPIO_ODR_ODR_5; //resets output data register
}

void LED_OFF(void){
	GPIOA->ODR |= 1U<<5; //assigns a specific output value to pin 5 is 1
		//GPIOA->ODR |= GPIO_ODR_ODR_5; //sets output value 1
}
