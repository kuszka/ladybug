/*******************************************************************************
			Konfiguracja plytki MOBOT-EXP MB oraz MOBOT-EXP MCB
********************************************************************************
ver. 1.0
Pawel Piatek
p.piatek@wobit.com.pl
WObit 2008
*******************************************************************************/

// sterowanie silnikami od kol napedowych
#define M1_IN1          PA3
#define M1_IN2          PA4
#define M1_P            PE4
#define M1_P_DDR        DDRE
#define M1_PORT         PORTA
#define M1_DDR          DDRA

#define M2_IN1          PA5
#define M2_IN2          PA6
#define M2_P            PE3
#define M2_P_DDR        DDRE
#define M2_PORT         PORTA
#define M2_DDR          DDRA

#define PIR1          	PB0
#define PIR1_PORT       PORTB
#define PIR1_DDR        DDRB

#define PIR2	        PB1
#define PIR2_PORT       PORTB
#define PIR2_DDR        DDRB

#define TRIG_DDR    	DDRB            // Trigger Port
#define TRIG_PORT   	PORTB
#define TRIG_PIN    	PINB
#define TRIG_BIT    	PB3             // Trigger Pin
 
#define ECHO_DDR    	DDRB            // Echo Port
#define ECHO_PORT   	PORTB
#define ECHO_PIN    	PINB
#define ECHO_BIT    	PB4             // Echo Pin

#define FS_AB           PC2
#define FS_AB_DDR       DDRC
#define FS_AB_PORT      PORTC
#define FS_AB_PIN       PINC

#define PG3_SLEEP           PG3
#define PG3_SLEEP_PORT      PORTG
#define PG3_SLEEP_DDR       DDRG
//sygnal PG3_SLEEP jest wspolny z driverem silnika krokowego

// diody
#define LED1			PD7
#define LED1_PORT     	PORTD
#define LED1_DDR     	DDRD

#define LED2			PD6
#define LED2_PORT     	PORTD
#define LED2_DDR     	DDRD
