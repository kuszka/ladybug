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
    int itmp;
	    
    ioinit();	
	UART0_init();					  
    TIMER_init();
    MOTOR_init();
    ADC_init();
	init_sonar();
    
    sei();	//globalne wlaczenie przerwan
    
	ADC_start_conversion();
	
	uint32_t distance=0;
	
	UART0_print("UART0 test\r\n");
	LED2_OFF;
	
	for(;;) //glowna petla programu
	{
		if(UART0_data_in_rx_buffer())
		{
			switch(rcv = UART0_receive_byte()){
				case 'v':
						UART0_print("Podaj nowa predkosc (-255 - 255): ");
						UART0_gets(tmp,8);
						itmp = atoi(tmp);
						UART0_print("\r\n");
						MOTOR_drive(itmp,itmp);
						break;		
					case 'b':
						MOTOR_break();						
						break;
					case 's':
						MOTOR_sleep();
						break;
					case 'r':
						MOTOR_drive(255,0);
						break;				
					case 'l':
						MOTOR_drive(0,255);
						break;
					case 'm':
						if((PINB & (1<<PIR2)))            // check for sensor pin PC.0 using bit
							{
								UART0_print("Janusz2");
							}
						break;
					case 'u':
						UART0_print("Ultrasonic: ");
						distance = read_sonar();
						char str[16];
						itoa (distance,str,10);
						UART0_print(str);
						UART0_print("\r\n");
						break;								
			}
		}		
	}
    
return 0;
}
