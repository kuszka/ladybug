/*******************************************************************************
  Glowna funkcja przykladowego programu do plytki MOBOT-EXP MB w raz z modulem 
						rozszerzen MOBOT-EXP MCB
********************************************************************************
ver. 1.0
Pawel Piatek
p.piatek@wobit.com.pl
WObit 2008

Opis:
	Plik zawiera glowna funkcje programu oraz funkcje inicjalizujaca 
wyprowadzenia mikrokontrolera. W funkcji glownej wywolywane sa najpierw funkcje
inicjalizujace poszczegolne uzyte uklady peryferyjne mikrokontrolera, nastepnie
w glownej petli oczekuje na odbior polecen przez UART odpowiednio na nie reagujac.
Program mo¿na testowaæ za pomoc¹ dowolnego terminala.
Ustawienia portu COM:
57600 8N1
*******************************************************************************/
#include "Main.h"


/*******************************************************************************
Funkcja:
	void ioinit(void)
Argumenty: 
	- brak
Opis:
	Wstepna Inicjalizacja wejsc/wyjsc
*******************************************************************************/
void ioinit(void)
{
	M1_DDR |= (1<<M1_IN1)|(1<<M1_IN2)|(1<<M2_IN1)|(1<<M2_IN2); //jako wyjscia
	M1_P_DDR |= (1<<M1_P)|(1<<M2_P); //piny od PWMa jako wyjscia

	PG3_SLEEP_DDR |= (1<<PG3_SLEEP); //jako wyjscie
	PG3_SLEEP_PORT &= ~(1<<PG3_SLEEP); //uspienie silnikow	
	FS_AB_DDR &= ~(1<<FS_AB);  //pinod FS jako wejscie	
	
	LED1_DDR |= (1<<LED1)|(1<<LED2); //jako wyjscia
	
	PIR2_DDR &= ~(1<<PIR2);
	PIR1_DDR &= ~(1<<PIR1);
	
	DDRF = 0x00; //caly port jako wejscie (konieczne gdy uzywamy ADC)
}

/*******************************************************************************
Funkcja:
	int main(void)
Argumenty: 
	- brak
Opis:
	Glowna funkcja programu
*******************************************************************************/
int main(void)
{
    unsigned char rcv;
    char tmp[8];
	double output[2];
	uint32_t ultrasonics[2];
	float ultrasonics_normalized[2];
	int pir_l;
	int pir_r;
	    
    ioinit();	
	UART0_init();					  
    TIMER_init();
    MOTOR_init();
    //ADC_init();
	init_sonar();
    sei();	//globalne wlaczenie przerwan
	
	//uint32_t distance = 0;
    
	//ADC_start_conversion();
	
	UART0_print("UART0 test\r\n");
	LED2_OFF;
	int state =2;
	int i;
	
	for(;;) //glowna petla programu
	{	
		switch(state){
			case 1:
				i = 0;
				while(i<10){
					if(UART0_data_in_rx_buffer()){
						i=0;
						switch(rcv = UART0_receive_byte()){	
							case 'b':
								MOTOR_break();						
							break;					
						}
					}
			
					ultrasonics[0] = 0;
					ultrasonics[1] = 0;
					read_sonar(ultrasonics);
					pir_l = 0;
					pir_r = 0;
					//char out[10];
					//char out1[10];
									
					if((PINB & (1<<PIR2)))            // check for sensor pin PC.0 using bit
					{
						pir_l = 1;
					}
									
					if((PINB & (1<<PIR1)))            // check for sensor pin PC.0 using bit
					{
						pir_r = 1;
					}
									
					if(ultrasonics[0] > 100)            // check for sensor pin PC.0 using bit
					{
						ultrasonics[0] = 100;
					}
									
					if(ultrasonics[1] > 100)            // check for sensor pin PC.0 using bit
					{
						ultrasonics[1] = 100;
					}
					ultrasonics_normalized[0]= ultrasonics[0]/100;
					ultrasonics_normalized[1]= ultrasonics[1]/100;
					output[0] = 0;
					output[1] = 0;
					network(output, ultrasonics_normalized[1], ultrasonics_normalized[0], pir_l, pir_r);
					//dtostrf(output[0], 10, 5, out);
					//dtostrf(output[1], 10, 5, out1);
					//UART0_print(out);
					//UART0_print("\r\n");
					//UART0_print(out1);
					//UART0_print("\r\n");
					int left = (int)(output[0]*255);
					int right = (int)(output[1]*255);
					if ((left<50) & (right < 50)){
						MOTOR_sleep();
					}
					else{
						MOTOR_drive(right,left);
					}
					i++;
				}
				MOTOR_break();
				state = 2;
				break;
			case 2:
				if(UART0_data_in_rx_buffer()){
					switch(rcv = UART0_receive_byte()){	
						case 'a':
							state = 1;						
						break;					
					}
				}
				break;
			default:
				state = 2;
				break;
		}
    }
	return 0;
}
