#ifndef INC_PERFORM_FFT_H_
#define INC_PERFORM_FFT_H_

#include "stm32l4xx.h"

#include "arm_math.h"
#include "defines.h"

extern float32_t fft_input_buffer[2 * N];
extern float32_t fft_output_buffer[N];

extern arm_cfft_radix2_instance_f32 cfft_instance;

typedef struct{
	float f;
	float A;
} DetectedComponent;

void perform_fft(float *I, float *Q);

#endif /* INC_PERFORM_FFT_H_ */
