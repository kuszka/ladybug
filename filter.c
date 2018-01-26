#include "main.h"

int cmpfunc (const void * a, const void * b) {
   return ( *(uint32_t*)a - *(uint32_t*)b );
}

void median_filter(uint32_t output[]){
	ultrasonics[0] = 0;
	ultrasonics[1] = 0;
	for(int i=0; i<BUFFER_SIZE; i++){
		read_sonar(ultrasonics);
		buffer_right[i] = ultrasonics[0];
		buffer_left[i] = ultrasonics[1];
	}
	qsort(buffer_right, BUFFER_SIZE, sizeof(uint32_t), cmpfunc);
	qsort(buffer_left, BUFFER_SIZE, sizeof(uint32_t), cmpfunc);
	output[0] = buffer_right[4];
	output[1] = buffer_left[4];
	
}