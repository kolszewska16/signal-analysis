#include "init_time_array.h"

#include "main.h"

#include "defines.h"

/**
 * @brief Initializes a global time array with evenly spaced time samples
 *
 * @retval None
 *
 * @note This function assumes the existence of the following global variables:
 * - `t`: A float array to store the time samples
 * - `N`: The total number of samples to be generated
 * - `FS`: The sampling frequency in Hz (samples per second)
 */
void init_time_array(void){
	float dt = 1.0f / FS;
	for(int i = 0; i < N; i++){
		t[i] = i * dt;
	}
}
