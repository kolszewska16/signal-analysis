#include "bubbleSort.h"

/**
 * @brief Sorts an array of floating-point numbers in ascending order using the Bubble Sort algorithm
 *
 * @param[in] arr Pointer to the array of floating-point numbers to be sorted
 * @param[in] n The number of elements in the array
 *
 * @retval None
 */
void bubbleSort(float *arr, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(arr[j] > arr[j + 1]){
				float temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
