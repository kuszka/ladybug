#ifndef __SONARL_H_
#define __SONARL_H_
 
/** ...- . . .-. --- -... --- -
 * @brief   Initiate Ports for Trigger and Echo pins
 * @param   void
 * @return  none
*/
void init_sonar_l(void);
 
/**  ...- . . .-. --- -... --- -
 * @brief   Send 10us pulse on Ultrasonic Trigger pin
 * @param   void
 * @return  none
*/
void trigger_sonar_l(void);
 
/**  ...- . . .-. --- -... --- -
 * @brief   Calculate and store echo time and return distance
 * @param   void
 * @return  unsigned int
 * Usage    int foo = read_sonar();
*/
uint32_t read_sonar_l(void);
 
#endif /* __SONARL_H_ */