#include "rng.h"

#include "main.h"

extern RNG_HandleTypeDef hrng;

/*
 * @brief Generates a pseudo-random floating-point number within a specified range
 *
 * @param[in] min The minimum value of the desired range
 * @param[in] max The maximum value of the desired range
 *
 * @retval A pseudo-random floatin-point number within the [min, max] range
 *
 * @note This function uses the hardware Random Number Generator (RNG) peripheral of the STM32 microcontroller
 * It requires the RNG peripheral to be initialized via a `RNG_HandleTypeDef` struct (e.g. `hrng`) and the `HAL_GenerateRandomNumber` function must be available
 * The `Error_Handler` is called if random number generation fails
 *
 * @warning The generated number is pseudo-random, relying on the entropy of the hardware RNG
 * The quality of the randomness depends on the specific microcontroller's implementation
 */
float rng(float min, float max){
	uint32_t random_int;
	if(HAL_RNG_GenerateRandomNumber(&hrng, &random_int) != HAL_OK){
		Error_Handler();
	}
	float random_float = (float)random_int / UINT32_MAX;
	return min + (random_float * (max - min));
}
