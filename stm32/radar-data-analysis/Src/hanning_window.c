#include "hanning_window.h"

#include <math.h>
#include "defines.h"

extern float fft_input_buffer[2 * N];

/**
 * @brief Applies a Hanning window to a complex signal represented by I and Q components
 *
 * @param[in] I Pointer to the array of in-phase (I) signal components
 * @param[in] Q Pointer to the array of quadrature (Q) signal components
 * @param[out] arr Pointer to the output array where the windowed complex signal will be stored
 * @param[in] n The number of samples in the I and Q signal arrays
 *
 * @retval None
 *
 * @note The output array `arr` must be large enough to hold twice the number of samples(`2 * n`) as the windowed I and Q are stored interleaved
 */
void hanning_window(float *I, float *Q, float *arr, int n){
	for(int i = 0; i < n; i++){
		float window = 0.5 * (1 - cosf((2.0f * M_PI * i) / (float)(n - 1)));
		arr[2 * i] = I[i] * window;
		arr[2 * i + 1] = Q[i] * window;
	}
}
