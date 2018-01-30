#ifndef __SONAR_H_
#define __SONAR_H_
 
void init_sonar(void);
void trigger_sonar_left(void);
void trigger_sonar_right(void);
void read_sonar(uint32_t ultrasonics[]);
 
#endif /* __SONAR_H_ */