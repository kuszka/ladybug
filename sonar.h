#ifndef __SONAR_H_
#define __SONAR_H_
 
/** ...- . . .-. --- -... --- -
 * @brief   Initiate Ports for Trigger and Echo pins
 * @param   void
 * @return  none
*/
void init_sonar(void);
 
/**  ...- . . .-. --- -... --- -
 * @brief   Send 10us pulse on Ultrasonic Trigger pin
 * @param   void
 * @return  none
*/
void trigger_sonar_left(void);
void trigger_sonar_right(void);
 
/**  ...- . . .-. --- -... --- -
 * @brief   Calculate and store echo time and return distance
 * @param   void
 * @return  unsigned int
 * Usage    int foo = read_sonar();
*/
void read_sonar(uint32_t ultrasonics[]);
 
#endif /* __SONAR_H_ */