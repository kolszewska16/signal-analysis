#include "calculate_median.h"

#include "main.h"
#include "defines.h"
#include "bubbleSort.h"

/**
 * @brief Calculates the median of a given array of floating-point numbers
 *
 * @param[in] arr Pointer to the input array of floating-point numbers
 * @param[in] n The number of elements in the array
 *
 * @retval The median value of the array
 *
 * @note This function creates a temporary copy of the array and sorts it using the `bubbleSort` function
 * The original input array is not modified
 * The `bubbleSort` function must be available in the project
 */
float calculate_median(float *arr, int n){
	float temp_buffer[n];
	for(int i = 0; i < n; i++){
		temp_buffer[i] = arr[i];
	}

	bubbleSort(temp_buffer, n);

	//median
	//odd number of elements
	if(n % 2 != 0){
		return temp_buffer[n / 2];
	}
	//even number of elements
	else{
		return (temp_buffer[n / 2 - 1] + temp_buffer[n / 2]) / 2.0f;
	}
}
