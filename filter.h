#ifndef __FILTER_H_
#define __FILTER_H_

#define BUFFER_SIZE 9
 
uint32_t buffer_left[BUFFER_SIZE];
uint32_t buffer_right[BUFFER_SIZE];
uint32_t result_left;
uint32_t result_right;
uint32_t ultrasonics[2];

void median_filter(uint32_t output[]);
int cmpfunc (const void * a, const void * b);
 
#endif /* __FILTER_H_ */