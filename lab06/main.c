/******************************************
#
# Anindita Deb, Summer 2022
# CPE 3000 Lab06
#
# Description: I will create a project that will control the keypad to create
# a locking and unlocking system. I will indicate when the system is locked and
# unlock it using the last 6 numbers of my student ID which are 922115.
#
# ==Usage==
#
#-
#-
#-
#
******************************************/

#include "stm32l476xx.h" //these are the files that have been provided and imported
#include "core_cm4.h"


//Define your function prototypes here.
extern int add_asm(int,int,int,int); 	//using external assembly file

void delay();				//naming the delay function
void LED_Init(void);		//naming LED initial state function
void BUTTON_Init(void);		//namimg the button's inital state function
void KEYPAD_Init(void);
void LED_ON(void);			//naming LED ON function
void LED_OFF(void);			//naming LED OFF function
uint32_t mask;				//define mask variable
uint32_t input;				//define input variable


int main(void){

//Write code here
	LED_Init(); 	//calling the initialized function
	BUTTON_Init();  //calling the button function
	KEYPAD_Init();  //calling the keypad function
	LED_OFF(); 		//calling the off function
	//LED (LD2)will be off when initally reset to signify unlocked
	//LED (LD2) will only turn on after user input button is pressed to signify "locked"

	int v, w, x, y, z;

	while(1){

		//set rows HIGH which is 1
		GPIOA->ODR |= GPIO_ODR_ODR_6;	//GPIOA port 6 bit set to 1
		GPIOA->ODR |= GPIO_ODR_ODR_7;	//GPIOA port 7 bit set to 1
		GPIOB->ODR |= GPIO_ODR_ODR_6;	//GPIOB port 6 bit set to 1
		GPIOC->ODR |= GPIO_ODR_ODR_7;	//GPIOB port 7 bit set to 1

		//KEYPAD #9
		delay(10);
		//set row 3 low
		GPIOB->ODR &= ~GPIO_ODR_ODR_6;
		delay(10);
		//read column 3
		mask= 1UL<<10;
		input = (GPIOB->IDR&mask) == mask;
		delay(10);
		v=9;

		//KEYPAD #2
		delay(10);
		//set row 1 low
		GPIOA->ODR &= ~GPIO_ODR_ODR_6;
		delay(10);
		//read column 2
		mask= 1UL<<8;
		input = (GPIOA->IDR&mask) == mask;
		delay(10);
		w=2;

		//KEYPAD #1
		delay(10);
		//set row 1 low
		GPIOA->ODR &= ~GPIO_ODR_ODR_6;
		delay(10);
		//read column 1
		mask= 1UL<<9;
		input = (GPIOA->IDR&mask) == mask;
		delay(10);
		x=1;

		//KEYPAD #5
		delay(10);
		//set row 2 low
		GPIOA->ODR &= ~GPIO_ODR_ODR_7;
		delay(10);
		//read column 2
		mask= 1UL<<8;
		input = (GPIOA->IDR&mask) == mask;
		delay(10);
		y=5;

		mask = 1UL<<13; //reading the user input button's pin PC13 (blue button)
		input = (GPIOC ->IDR&mask) == mask;

		if(input == 0){
		//input=0 means user button is pressed
		LED_ON(); //the LD2 must be on

		if(input==0){ //if blue user button pressed
		v=9;
		w=2;
		x=1;
		y=5;
		z = add_asm(v,w,x,y); //recall external file
		delay(50);
		} else{
				LED_OFF();
				delay(50);
			}
		if(z==20){
			LED_ON();
			delay(50);
			z=0;
		}else{
				LED_OFF();
				delay(5);
		}
	}//continuous while-loop
}
}//END main


//Implement the function protoypes here.
void delay(int counter){
	int i;
	for(i=0; i<counter*1000; i++){

	}
}

void LED_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enables the clock for port A

	GPIOA->MODER &= ~(3U<<(2*5)); //clear mode bits of 2*Pin 5
	GPIOA->MODER |=1U<<(2*5); //set mode to output

	GPIOA->OTYPER &= ~(1U<<(5)); //push-pull output type selected

	GPIOA->PUPDR &= ~(3U<<(2*5)); //output defined as no pull up, no pull down (00)
}

void BUTTON_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //Enables the clock for port C
	GPIOC->MODER &= ~(3U<<(2*13)); //clear mode bits of pin13 and use as input
	GPIOC->PUPDR &= ~(3U<<(2*13)); //output
	GPIOC->PUPDR |= (2UL<<(2*13)); //defined as pull down (10)

}

void KEYPAD_Init(void){
	//the GPIO pins I want to use for the keypad
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock

	//INITIALIZE GPIO OUTPUTS
	//Row 1: PA6
	GPIOA->MODER &= ~(3U<<(2*6)); //clear mode bits of 2*Pin 6
	GPIOA->MODER |=1U<<(2*6); //set mode to output
	GPIOA->OTYPER &= ~(1U<<(6)); //push-pull output type selected
	GPIOA->PUPDR &= ~(3U<<(2*6)); //output defined as no pull up, no pull down (00)
	//Row 2: PA7
	GPIOA->MODER &= ~(3U<<(2*7)); //clear mode bits of 2*Pin 7
	GPIOA->MODER |=1U<<(2*7); //set mode to output
	GPIOA->OTYPER &= ~(1U<<(7)); //push-pull output type selected
	GPIOA->PUPDR &= ~(3U<<(2*7)); //output defined as no pull up, no pull down (00)
	//Row 3: PB6
	GPIOB->MODER &= ~(3U<<(2*6)); //clear mode bits of 2*Pin 6
	GPIOB->MODER |=1U<<(2*6); //set mode to output
	GPIOB->OTYPER &= ~(1U<<(6)); //push-pull output type selected
	GPIOB->PUPDR &= ~(3U<<(2*6)); //output defined as no pull up, no pull down (00)
	//Row 4: PC7
	GPIOC->MODER &= ~(3U<<(2*7)); //clear mode bits of 2*Pin 7
	GPIOC->MODER |=1U<<(2*7); //set mode to output
	GPIOC->OTYPER &= ~(1U<<(7)); //push-pull output type selected
	GPIOC->PUPDR &= ~(3U<<(2*7)); //output defined as no pull up, no pull down (00)

	//INITIALIZE GPIO INPUTS
	//Column 1: PA9
	GPIOA->MODER &= ~(3U<<(2*9)); //clear mode bits of pin9 and use as input
	GPIOA->PUPDR &= ~(3U<<(2*9)); //output
	GPIOA->PUPDR |= (1UL<<(2*9)); //defined as pull down
	//Column 2: PA8
	GPIOA->MODER &= ~(3U<<(2*8)); //clear mode bits of pin8 and use as input
	GPIOA->PUPDR &= ~(3U<<(2*8)); //output
	GPIOA->PUPDR |= (1UL<<(2*8)); //defined as pull down
	//Column 3: PB10
	GPIOB->MODER &= ~(3U<<(2*10)); //clear mode bits of pin10 and use as input
	GPIOB->PUPDR &= ~(3U<<(2*10)); //output
	GPIOB->PUPDR |= (1UL<<(2*10)); //defined as pull down (10)
	//Column 4: PB4
	GPIOB->MODER &= ~(3U<<(2*4)); //clear mode bits of pin4 and use as input
	GPIOB->PUPDR &= ~(3U<<(2*4)); //output
	GPIOB->PUPDR |= (1UL<<(2*4)); //defined as pull down (10)

}

void LED_ON(void){
	//GPIOA->ODR |= 1U<<5; //assigns a specific output value to pin 5 is 1
	GPIOA->ODR |= GPIO_ODR_ODR_5; //sets output value 1

}

void LED_OFF(void){
	//GPIOA->ODR &= 0U<<5; //assigns a specific output value to pin 5 is 0
	GPIOA->ODR &= ~GPIO_ODR_ODR_5; //resets output data register
}
