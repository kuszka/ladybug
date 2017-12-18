#include "main.h"
 
volatile uint32_t overFlowCounter = 0;
volatile uint32_t trig_counter = 0;
volatile uint32_t no_of_ticks = 0;
 
/********** ...- . . .-. --- -... --- - *********************************
 * Initiate Ultrasonic Module Ports and Pins
 * Input:   none
 * Returns: none
*********** ...- . . .-. --- -... --- - *********************************/
void init_sonar(void){
    TRIG_DDR |= (1<<TRIG_BIT);     // Set Trigger pin as output
    ECHO_DDR &= ~(1<<ECHO_BIT);     // Set Echo pin as input
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Send 10us pulse on Sonar Trigger pin
 * 1.   Clear trigger pin before sending a pulse
 * 2.   Send high pulse to trigger pin for 10us
 * 3.   Clear trigger pin to pull it trigger pin low
 *  Input:   none
 *  Returns: none
********** ...- . . .-. --- -... --- - *********************************/
void trigger_sonar(void){
    TRIG_PORT &= ~(1<<TRIG_BIT);             // Clear pin before setting it high
    _delay_us(1);           // Clear to zero and give time for electronics to set
    TRIG_PORT |=(1<<TRIG_BIT);            // Set pin high
    _delay_us(12);          // Send high pulse for minimum 10us
    TRIG_PORT &= ~(1<<TRIG_BIT);              // Clear pin
    _delay_us(1);           // Delay not required, but just in case...
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Increment timer on each overflow
 * Input:   none
 * Returns: none
********** ...- . . .-. --- -... --- - *********************************/
 
/********** ...- . . .-. --- -... --- - *********************************
 * Calculate and store echo time and return distance
 * Input:   none
 * Returns: 1. -1       :   Indicates trigger error. Could not pull trigger high
 *          2. -2       :   Indicates echo error. No echo received within range
 *          3. Distance :   Sonar calculated distance in cm.
********** ...- . . .-. --- -... --- - *********************************/
uint32_t read_sonar(void){

	uint32_t i,result;
	trigger_sonar();
	//Wait for the rising edge
	i=0;
	for(i=0;i<600000;i++)
	{
		if(!(ECHO_PIN & (1<<ECHO_BIT))) 
			continue;	//Line is still low, so wait
		else 
			break;		//High edge detected, so break.
	}

	if(i==600000)
		return 0;	//Indicates time out
	
	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B|=(1<<CS11) ;	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<600000;i++)
	{
		if((ECHO_PIN & (1<<ECHO_BIT)))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
			break;
	}

	if(i==600000)
		return 1;	//Indicates time out

	//Falling edge found

	result=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
		return 2;	//No obstacle
	else
		return i/58.0f;
}