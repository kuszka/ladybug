/*******************************************************************************
						Sterowanie silnikami DC
********************************************************************************
ver. 1.0
Pawel Piatek
p.piatek@wobit.com.pl
WObit 2008

Opis:
	Pliik zawiera definicje symboli oraz deklaracje funkcji do sterowania 
silnikami DC.
*******************************************************************************/
#ifndef __MOTOR_H
#define __MOTOR_H

#define PWM_MAX 			255 
#define PWM34_MAX 			255
#define PWM56 				128 //da wspolczynnik wypelnienia 50%

//deklaracje funkcji
void MOTOR_init(void);
void MOTOR_drive(signed int left_speed,signed int right_speed); 
void MOTOR_break(void);
void MOTOR_sleep(void);

#endif //__MOTOR_H
