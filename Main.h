#ifndef _MAIN_H_
#define _MAIN_H_

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "io_cfg.h"
#include "motor.h"
#include "timer.h"
#include "sonar.h"
#include "Uart.h"
#include "network.h"
#include "filter.h"

void setState(void);
void calculateOutput(void);
void sonarPrint(void);

// diody
#define LED1_OFF        LED1_PORT|=(1<<LED1)
#define LED1_ON        LED1_PORT&=~(1<<LED1)
#define LED1_TOGGLE     LED1_PORT^=(1<<LED1)

#define LED2_OFF         LED2_PORT|=(1<<LED2)
#define LED2_ON        LED2_PORT&=~(1<<LED2)
#define LED2_TOGGLE     LED2_PORT^=(1<<LED2)

#define ITERATE		50

#endif//_MAIN_H_
