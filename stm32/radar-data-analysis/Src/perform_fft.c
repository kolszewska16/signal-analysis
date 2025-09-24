#include "perform_fft.h"

#include <stdio.h>
#include <math.h>
#include "arm_math.h"

#include "defines.h"
#include "hanning_window.h"
#include "calculate_median.h"

/**
 * @brief Performs Fast Fourier Transform (FFT) on a complex signal to analyze its components and detected peaks
 *
 * @param[in] I Pointer to the array containing the in-phase (I) signal data
 * @param[in] Q Pointer to the array containing the quadrature (Q) signal data
 *
 * @retval None
 *
 * @note This function assumes the existence of several global variables:
 * - `arm_cfft_radix2_instace_f32`: Struct named `cfft_instance`
 * - `fft_input_buffer`: An array for floating-point numbers of size `2 * N`. This buffer is used to hold complex input signal for the FFt
 * - `fft_output_buffer`: An array for floating-point numbers of size `N`. This buffer is used to to store the magnitude (or amplitude) of the frequency spectrum after the computed FFT
 * - `N`: Number of samples
 * - `K`: Number of targets
 * - `FS`: Sampling frequency
 * It relies on the `hanning_window` and `calculate_median` functions to be implemented and available in the project
 *
 * @warning This function uses `printf` for debugging output which may not be suitable for all real-time or resource-constrained embedded systems due to its overhead
 * This output should be removed or replaced in the final application
 *
 * @see hanning_window
 * @see calculate_median
 */
void perform_fft(float *I, float *Q){
	hanning_window(I, Q, fft_input_buffer, N);

	//FFT
	arm_cfft_radix2_init_f32(&cfft_instance, N, 0, 1);
	arm_cfft_radix2_f32(&cfft_instance, fft_input_buffer);

	arm_cmplx_mag_f32(fft_input_buffer, fft_output_buffer, N);

	//normalization
	for(int i = 0; i < N / 2; i++){
		fft_output_buffer[i] = 2 * fft_output_buffer[i] / N;
	}

	DetectedComponent detected[2 * K];
	int detected_count = 0;
	float32_t threshold = 75.0f * calculate_median(fft_output_buffer, N / 2);

	for(int i = 1; i < N / 2 - 1; i++){
		if((fft_output_buffer[i] > threshold) && (fft_output_buffer[i] > fft_output_buffer[i - 1]) && (fft_output_buffer[i] > fft_output_buffer[i + 1])){
			if(detected_count < 2 * K){
				detected[detected_count].f = (float)i * FS / N;
				detected[detected_count].A = fft_output_buffer[i];
				detected_count++;
			}
		}
	}

	int errors_count = 0;

	printf("\n");
	printf("DETECTED:\n");
	for(int i = 0; i < detected_count; i++){
	float32_t acceleration = detected[i].A * powf((2.0 * M_PI * detected[i].f), 2.0);
		if(acceleration <= 0.8){
			printf("%d. frequency: %f Hz | amplitude: %f m | acceleration: %f m/s^2\n", i + 1, detected[i].f, detected[i].A, acceleration);
		}
		else{
			printf("ERROR! frequency: %f Hz | amplitude: %f m | acceleration: %f m/s^2\n", detected[i].f, detected[i].A, acceleration);
			errors_count++;
		}
	}

	printf("\n");
	printf("SUMMARY:\n");
	printf("%d out of %d frequencies\n", detected_count, K);
	printf("number of errors: %d\n", errors_count);
	printf("threshold: %f\n", threshold);
}
