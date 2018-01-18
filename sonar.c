#include "main.h"
 
 
/********** ...- . . .-. --- -... --- - *********************************
 * Initiate Ultrasonic Module Ports and Pins
 * Input:   none
 * Returns: none
*********** ...- . . .-. --- -... --- - *********************************/
void init_sonar(void){
    TRIG_L_DDR |= (1<<TRIG_L_BIT);     // Set Trigger pin as output
    ECHO_L_DDR &= ~(1<<ECHO_L_BIT);     // Set Echo pin as input
	TRIG_R_DDR |= (1<<TRIG_R_BIT);     // Set Trigger pin as output
    ECHO_R_DDR &= ~(1<<ECHO_R_BIT);     // Set Echo pin as input
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Send 10us pulse on Sonar Trigger pin
 * 1.   Clear trigger pin before sending a pulse
 * 2.   Send high pulse to trigger pin for 10us
 * 3.   Clear trigger pin to pull it trigger pin low
 *  Input:   none
 *  Returns: none
********** ...- . . .-. --- -... --- - *********************************/
void trigger_sonar_left(void){
    // Clear pin before setting it high
	TRIG_L_PORT &= ~(1<<TRIG_L_BIT);
    _delay_us(1);           // Clear to zero and give time for electronics to set
  	TRIG_L_PORT |=(1<<TRIG_L_BIT);// Set pin high
    _delay_us(12);          // Send high pulse for minimum 10us  
	TRIG_L_PORT &= ~(1<<TRIG_L_BIT); // Clear pin
    _delay_us(1);           // Delay not required, but just in case...
}
void trigger_sonar_right(void){
    TRIG_R_PORT &= ~(1<<TRIG_R_BIT);             // Clear pin before setting it high
    _delay_us(1);           // Clear to zero and give time for electronics to set
    TRIG_R_PORT |=(1<<TRIG_R_BIT);  // Set pin high
    _delay_us(12);          // Send high pulse for minimum 10us
    TRIG_R_PORT &= ~(1<<TRIG_R_BIT);  // Clear pin
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
void read_sonar(uint32_t ultrasonics[]){

	uint32_t i, result_left, result_right;
	trigger_sonar_right();
	//Wait for the rising edge
	i=0;
	for(i=0;i<600000;i++)
	{
		if(!(ECHO_R_PIN & (1<<ECHO_R_BIT))) 
			continue;	//Line is still low, so wait
		else 
			break;		//High edge detected, so break.
	}

	if(i==600000)
		ultrasonics[0] = 0;	//Indicates time out
	
	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B|=(1<<CS11) ;	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<60000;i++)
	{
		if((ECHO_R_PIN & (1<<ECHO_R_BIT)))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
			break;
	}

	if(i==60000)
		ultrasonics[0] = 1;	//Indicates time out

	//Falling edge found

	result_right=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result_right > 60000)
		ultrasonics[0] = 2;	//No obstacle
	else
		ultrasonics[0] = result_right/116;
		

	// LEFT
	trigger_sonar_left();
	i=0;
	
	for(i=0;i<600000;i++)
	{
		if(!(ECHO_L_PIN & (1<<ECHO_L_BIT))) 
			continue;	//Line is still low, so wait
		else 
			break;		//High edge detected, so break.
	}

	if(i==600000)
		ultrasonics[1] = 0;	//Indicates time out
	
	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B|=(1<<CS11) ;	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<60000;i++)
	{
		if((ECHO_L_PIN & (1<<ECHO_L_BIT)))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
			break;
	}

	if(i==60000)
		ultrasonics[1] = 1;	//Indicates time out

	//Falling edge found

	result_left=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result_left > 60000)
		ultrasonics[1] = 2;	//No obstacle
	else
		ultrasonics[1] = result_left/116;
}