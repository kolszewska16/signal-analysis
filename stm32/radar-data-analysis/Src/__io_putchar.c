#include "__io_putchar.h"

#include "main.h"

extern UART_HandleTypeDef huart2;

/**
 * @brief This function is a custom implementation of `__io_putchar` used by `printf` function
 * It redirects character output to the specified UART peripheral
 *
 * @param[in] ch The character to be transmitted
 *
 * @retval Always returns 1, indicating that the operation was successful
 *
 * @note This function handles new line character `\n` by also transmitting a carriage return `\r` which is necessary for proper line breaks in a terminal emulator
 * It relies on the global `huart2` handler to be properly initialized for the UART peripheral
 * The transmission is blocking due to the use of `HAL_MAX_DELAY`
 */
int __io_putchar(int ch){
	if(ch == '\n'){
		uint8_t ch2 = '\r';
		HAL_UART_Transmit(&huart2, &ch2, 1, HAL_MAX_DELAY);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return 1;
}
