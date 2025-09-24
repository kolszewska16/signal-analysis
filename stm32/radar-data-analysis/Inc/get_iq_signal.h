#ifndef INC_GET_IQ_SIGNAL_H_
#define INC_GET_IQ_SIGNAL_H_

#include "stm32l4xx.h"

#include "defines.h"

extern float t[N];
extern float I[N];
extern float Q[N];

void get_iq_signal(float *I, float *Q, int k);

#endif /* INC_GET_IQ_SIGNAL_H_ */
