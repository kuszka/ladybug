/*******************************************************************************
						Sterowanie silnikami DC
********************************************************************************
ver. 1.0
Pawel Piatek
p.piatek@wobit.com.pl
WObit 2008

Opis:
	Pliik zawiera funkcje do sterowania driverami silnikow DC na p³ycie 
MOBOT-EXP MB oraz dodatkowymi driverami na plycie rozszerzen MOBOT-EXP MCB
*******************************************************************************/
#include "main.h"

/*******************************************************************************
Funkcja:
	void MOTOR_init(void)
Argumenty: 
	- brak
Opis:
	Inicjalizacja timera 3 do generowania sygnalu PWM (Pulse Width Modulation)
o rozdzielczosci 8 bitow i czestotliwosci ok 4kHz
*******************************************************************************/
void MOTOR_init(void)
{
  	TCCR3A |= (1<<COM3A1)|(1<<COM3B1)|(1<<COM3A0)|(1<<COM3B0)|(1<<WGM30);   
    TCCR3B |= (1<<CS31); //8bit Phase Correct PWM inverting mode dla silników kó³
						//preskaler przez 8 co da czêstotliwoœæ ok 4kHz

  	PG3_SLEEP_PORT &= ~(1<<PG3_SLEEP); //uspienie silnikow	
}

/*******************************************************************************
Funkcja:
	void MOTOR_drive(signed int left_speed,signed int right_speed)
Argumenty: 
	- signed int left_speed - wspolczynnik wypelnienia dla silnika od lewego 
		kola, mozna zadawac watosci z przedzialu -255 - 255, kierunek obrotu 
		zalezy od znaku 
	- signed int right_speed - wspolczynnik wypelnienia dla silnika od prawego 
		kola, mozna zadawac watosci z przedzialu -255 - 255, kierunek obrotu 
		zalezy od znaku 
Opis:
	Funkcja wyprowadza drivery ze stanu uspienia jezeli przynajniej jedna 
predkosc zadana jest rozna od zera (nalezy pamietac, ze sygnal PG3_SLEEP jest 
wspolny z driverem silnika krokowego na plytce MOBOT-EXP MCB). Funkcja zmienia 
kierunek obrotu silnika (kierunki lewo i prawo sa umowne) w zaleznosci od znaku
wartosci zadanej oraz ogranicza wartosc zadana tak aby nie nastepowalo 
przepelnienie.
*******************************************************************************/
void MOTOR_drive(signed int left_speed,signed int right_speed)
{
	if((left_speed != 0) || (right_speed != 0))
		PG3_SLEEP_PORT |= (1<<PG3_SLEEP); //wybudzenie driverow DC ze stanu uspienia

	if(left_speed > 0) //obot w prawo
	{
		M1_PORT |= (1<<M1_IN1);
		M1_PORT &= ~(1<<M1_IN2);
	}
	else if(left_speed < 0) //obrot w lewo
	{
		M1_PORT &= ~(1<<M1_IN1);
		M1_PORT |= (1<<M1_IN2);
	}
	
	if(right_speed > 0) //obrot w prawo
	{
		M2_PORT |= (1<<M2_IN1);
		M2_PORT &= ~(1<<M2_IN2);
	}
	else if(right_speed<0) //obrot w lewo
	{
		M2_PORT &= ~(1<<M2_IN1);
		M2_PORT |= (1<<M2_IN2);
	}

    if(abs(right_speed) >= PWM_MAX) //ograniczenie wartosci maksymalnej
		OCR3A = PWM_MAX;
	else
		OCR3A = (unsigned char)(abs(right_speed));
	             
	  
    if(abs(left_speed) >= PWM_MAX) //ograniczenie wartosci maksymalnej
		OCR3B = PWM_MAX;
	else
		OCR3B = (unsigned char)(abs(left_speed));  
	
}
/*******************************************************************************
Funkcja:
	void MOTOR_break(void)
Argumenty: 
	- brak
Opis:
	Realizuje hamowanie przez zwarcie obu wyprowadzen silnikow do masy. Przydatna
da awaryjnego zatrzymania robota.
*******************************************************************************/
void MOTOR_break(void)
{
     MOTOR_drive(255,255);
     M1_PORT |=  (1<<M1_IN1);                     
     M1_PORT |=  (1<<M1_IN2);                     
     M2_PORT |=  (1<<M2_IN1);                     
     M2_PORT |=  (1<<M2_IN2);   
}
/*******************************************************************************
Funkcja:
	void MOTOR_sleep(void)
Argumenty: 
	- brak
Opis:
	Funkcja wprowadza drivery silnikow od kol napedowych oraz driver silnika 
krokowego w stan uspienia (wspolne wyprowadzenie PG3_SLEEP), obnizajac pobor 
pradu
*******************************************************************************/
void MOTOR_sleep(void)
{
	PG3_SLEEP_PORT &= ~(1<<PG3_SLEEP); //przejscie driverow DC w stan uspienia	
}

