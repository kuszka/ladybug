#ifndef __NETWORK_H_
#define __NETWORK_H_

#define INPUT_SIZE		4
#define HIDDEN_SIZE		5
#define OUTPUT_SIZE		2

extern const double weights_hidden[HIDDEN_SIZE][INPUT_SIZE];
extern const double bias_hidden[HIDDEN_SIZE];
extern const double bias_out[OUTPUT_SIZE];
extern const double weights_out[OUTPUT_SIZE][HIDDEN_SIZE];

void init_weights(void);
void network(double output[], double ultra_left, double ultra_right, double PIR_left, double PIR_right);
double map_values(double in_1, double max_in, double min_in, double max_out, double min_out);


#endif /* __NETWORK_H_ */