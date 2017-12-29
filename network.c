#include "main.h"
const double weights_hidden[HIDDEN_SIZE][INPUT_SIZE] = {
	{-1.58519693611334,	1.89855196098368, 0.482950221052438, -0.369279061582649},
	{-0.185725289119383, 2.19578675199360, 0.910864748851620, -1.37631366519833},
	{-2.29578458240783,	2.30528300437042, -0.782691665160098, 1.32898469684781},
	{0.254009521819180,	-0.290475462709622,	-2.84802349264771, -2.04247483528763},
	{0.362755601362326,	-3.10757031579078, 3.02268230643587, -2.06515544346130}
};
const double bias_hidden[HIDDEN_SIZE] = {
	-0.420367312000537, 2.66072658006958, 0.983843757784758, -0.812007368604981, 3.97368192356818
};
const double bias_out[OUTPUT_SIZE] = {
	-0.320375464621576,
	-1.05427904383715
};
const double weights_out[OUTPUT_SIZE][HIDDEN_SIZE] = {
	{-2.16599511469715,	-1.20308188511324, 0.632717479384773, -1.65436533180512, -0.136132471238167},
	{1.30759079539261, 0.486704697620971, 0.137919809101367, -1.68646298537118, -0.326572646910357}
};

double map_values(double in_1, double max_in, double min_in, double max_out, double min_out) {
	return (max_out - min_out)*(in_1 - min_in) / (max_in - min_in) + min_out;
};
void network(double output[], double ultra_left, double ultra_right, double PIR_left, double PIR_right)
{
	 //normalization
	 double input[INPUT_SIZE] = {ultra_left, ultra_right, PIR_left, PIR_right};
	 for (int i = 0; i < INPUT_SIZE; i++) {
		 input[i] = map_values(input[i], 1, 0, 1, -1);
	 }

	 double hidden_result[HIDDEN_SIZE] = { 0,0,0,0,0 };
	// compute hidden layer
	for (int i = 0; i<HIDDEN_SIZE; i++) {
		for (int j = 0; j<INPUT_SIZE; j++) {
			hidden_result[i] += input[j] * weights_hidden[i][j];
		}
		hidden_result[i] += bias_hidden[i];
		hidden_result[i] = 2 / (1 + exp(-2 * hidden_result[i])) - 1;
	}
	static double outer_result[OUTPUT_SIZE] = { 0,0 };
	// compute outer layer
	for (int m = 0;  m < OUTPUT_SIZE; m++) {
		for (int n = 0; n < HIDDEN_SIZE; n++) {
			outer_result[m] += hidden_result[n] * weights_out[m][n];
		}
		outer_result[m] += bias_out[m];
		outer_result[m] = 2 / (1 + exp(-2 * outer_result[m])) - 1;
	}
	//denormalization
	for (int i = 0; i < OUTPUT_SIZE; i++) {
		outer_result[i] = map_values(outer_result[i], 1, -1, 1, 0);
	}
	
	output[0] = outer_result[0];
	output[1] = outer_result[1];
}
