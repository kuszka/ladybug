/*************PINOUT************************/

// motor 1
#define M1_IN1          PA3
#define M1_IN2          PA4
#define M1_P            PE4
#define M1_P_DDR        DDRE
#define M1_PORT         PORTA
#define M1_DDR          DDRA

//motor 2
#define M2_IN1          PA5
#define M2_IN2          PA6
#define M2_P            PE3
#define M2_P_DDR        DDRE
#define M2_PORT         PORTA
#define M2_DDR          DDRA

// Right PIR sensor
#define PIR_R          	PB0
#define PIR_R_PORT      PORTB
#define PIR_R_DDR       DDRB
#define PIR_R_PIN    	PINB

// Left PIR sensor
#define PIR_L	        PC3
#define PIR_L_PORT      PORTC
#define PIR_L_DDR       DDRC
#define PIR_L_PIN    	PINC

// Left ultrasonic sensor
#define TRIG_L_DDR    	DDRB            
#define TRIG_L_PORT   	PORTB
#define TRIG_L_PIN    	PINB
#define TRIG_L_BIT    	PB2             
 
#define ECHO_L_DDR    	DDRB          
#define ECHO_L_PORT   	PORTB
#define ECHO_L_PIN    	PINB
#define ECHO_L_BIT    	PB3 

// Right ultrasonic sensor
#define TRIG_R_DDR    	DDRA 
#define TRIG_R_PORT   	PORTA
#define TRIG_R_PIN    	PINA
#define TRIG_R_BIT    	PA2 
 
#define ECHO_R_DDR    	DDRA  
#define ECHO_R_PORT   	PORTA
#define ECHO_R_PIN    	PINA
#define ECHO_R_BIT    	PA7   

//Sleep the motors
#define FS_AB           PC2
#define FS_AB_DDR       DDRC
#define FS_AB_PORT      PORTC
#define FS_AB_PIN       PINC

#define PG3_SLEEP           PG3
#define PG3_SLEEP_PORT      PORTG
#define PG3_SLEEP_DDR       DDRG

// diode
#define LED1			PD7
#define LED1_PORT     	PORTD
#define LED1_DDR     	DDRD

#define LED2			PD6
#define LED2_PORT     	PORTD
#define LED2_DDR     	DDRD
