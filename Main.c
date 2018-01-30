#include "Main.h"

unsigned char rcv;
double output[2];
uint32_t ultrasonics[2];
float ultrasonics_normalized[2];
int pir_l;
int pir_r;
int state =2;
int i=0;


void ioinit(void)
{
	M1_DDR |= (1<<M1_IN1)|(1<<M1_IN2)|(1<<M2_IN1)|(1<<M2_IN2);
	M1_P_DDR |= (1<<M1_P)|(1<<M2_P);

	PG3_SLEEP_DDR |= (1<<PG3_SLEEP); 
	PG3_SLEEP_PORT &= ~(1<<PG3_SLEEP); 
	FS_AB_DDR &= ~(1<<FS_AB);  
	
	LED1_DDR |= (1<<LED1)|(1<<LED2);
	
	PIR_R_DDR &= ~(1<<PIR_R);
	PIR_L_DDR &= ~(1<<PIR_L);
	BLT_STATE_DDR &= ~(1<<BLT_STATE);
	
	DDRF = 0x00;
}

// IN CASE OF DEBUG
void sonarPrint(void){
	ultrasonics[0] = 0;
	ultrasonics[1] = 0;
	UART0_print("Ultrasonic filtered: ");
 	median_filter(ultrasonics);
 	char str[16];
	char str2[16];
	itoa (ultrasonics[0],str,10);
	itoa (ultrasonics[1],str2,10);
 	UART0_print(str);
 	UART0_print("\r\n");
	UART0_print(str2);
 	UART0_print("\r\n");
}

void calculateOutput(void){
	ultrasonics[0] = 0;
	ultrasonics[1] = 0;
	median_filter(ultrasonics);
	pir_l = 0;
	pir_r = 0;
	char out[10];
	char out1[10];

	if((PIR_L_PIN & (1<<PIR_L))) 
	{
		UART0_print("LEFT \r\n");
		pir_l = 1;
	}
	if((PIR_R_PIN & (1<<PIR_R))) 
	{
		UART0_print("RIGHT \r\n");
		pir_r = 1;
	}
	if(ultrasonics[0] > 150)
	{
		ultrasonics[0] = 150;
	}
	
	if(ultrasonics[1] > 150)
	{
		ultrasonics[1] = 150;
	}
	ultrasonics_normalized[0]= ultrasonics[0]/150;
	ultrasonics_normalized[1]= ultrasonics[1]/150;
	output[0] = 0;
	output[1] = 0;
	network(output, ultrasonics_normalized[1], ultrasonics_normalized[0], pir_l, pir_r);
	dtostrf(output[0], 10, 5, out);
	dtostrf(output[1], 10, 5, out1);
	UART0_print(out);
	UART0_print("\r\n");
	UART0_print(out1);
	UART0_print("\r\n");
	sonarPrint();
	int left = (int)(output[0]*255);
	int right = (int)(output[1]*255);
	if ((left < 100) && (right < 100)){
		MOTOR_sleep();
	}
	else if((left>=100) && (right>=100)){
		MOTOR_drive(250,250);
	}
	else if(right>=100){
		MOTOR_drive(250,-200);
	}
	else if(left>=100){
		MOTOR_drive(-200,250);
	}
}

void setState(void){
	if(UART0_data_in_rx_buffer()){
		switch(rcv = UART0_receive_byte()){	
			case 'b':
				MOTOR_break();
				state = 2;
			break;
			case 'a':
				if(state == 2){
					state = 1;	
				}
			break;	
		}
	}
	
	if(state == 1){
		if(!(BLT_STATE_PIN & (1<<BLT_STATE))){
			MOTOR_break();
			state = 2;
		}
	}
}

int main(void)
{
	    
    ioinit();	
	UART0_init();					  
    TIMER_init();
    MOTOR_init();
	init_sonar();
    sei();	//globalne wlaczenie przerwan
	
	UART0_print("UART0 test\r\n");
	LED2_OFF;
	
	for(;;)
	{
		setState();
		switch(state){
			case 2:
			break;
			case 1:
				calculateOutput();
				//sonarPrint();
			break;
			default:
				UART0_print("error");
				MOTOR_break();
			break;
		}
		_delay_ms(50); 
    }
	UART0_print("bye!");
	return 0;
}



