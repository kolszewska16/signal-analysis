#include "get_iq_signal.h"

#include <stdio.h>
#include <math.h>

#include "defines.h"
#include "rng.h"
#include "__io_putchar.h"

/**
 * @brief Generate I and Q signals based on set of simulated targets
 *
 * @param[out] I Pointer to the array where the in-phase (I) signal data will be stored
 * @param[out] Q Pointer to the array where the quadrature (Q) signal data will be stored
 * @param[in] k The number of simulated targets (or signal components) to be generated
 *
 * @retval None
 *
 * @note The function assumes the existence of several global variables:
 * - `N`: The number of samples for the output I/Q signals
 * - `lambda`: The wavelength of the radar signal
 * - `phi0`: An initial phase shift
 * - `t`: An array of time samples for the signal
 * - `rng(min, max)`: A function that generates a random number within a specified range
 * - `MIN`: A minimum value of the target's velocity in meters per second
 * - `MAX`: A maximum value of the target's velocity in meters per second
 *
 * @warning This function uses `printf` for debugging output which may not be suitable for all real-time or resource-constrained embedded systems due to its overhead
 * This output should be removed or replaced in the final application
 *
 * @see rng
 */
void get_iq_signal(float *I, float *Q, int k){
	float velocity[k];
	float frequency[k];
	float amplitude[k];
	float phase;

	for(int i = 0; i < k; i++){
		velocity[i] = rng(MIN, MAX);
	}

	for(int i = 0; i < k; i++){
		frequency[i] = (2 * velocity[i]) / lambda;
		amplitude[i] = 0.8f / powf((2.0f * M_PI * ((2.0f * velocity[i]) / lambda)), 2.0f);
	}

	for(int i = 0; i < N; i++){
		I[i] = 0.0f;
		Q[i] = 0.0f;
	}

	for(int i = 0; i < k; i++){
		phase = rng(0, 2 * M_PI);
		for(int j = 0; j < N; j++){
			I[j] += amplitude[i] * cosf(phi0 + 2 * M_PI * frequency[i] * t[j] + phase);
			Q[j] += amplitude[i] * sinf(phi0 + 2 * M_PI * frequency[i] * t[j] + phase);
		}
	}

	printf("\n");
	printf("GENERATED:\n");
	for(int i = 0; i < k; i++){
		printf("%d. frequency: %f Hz | amplitude: %f m\n", i + 1, frequency[i], amplitude[i]);
	}
}
