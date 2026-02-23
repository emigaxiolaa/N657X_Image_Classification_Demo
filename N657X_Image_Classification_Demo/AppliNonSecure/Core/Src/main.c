/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "network.h"
#include "app_x-cube-ai.h"
#include "stai_network.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// 1. Manejador oficial de la IA
stai_network network;           // Objeto de la red
stai_return_code stai_ret;      // Para capturar errores del N6
stai_buffer *ai_input;          // Buffers para entrada
stai_buffer *ai_output;         // Buffers para salida

__attribute__((aligned(32))) uint8_t activations[245760];

UART_HandleTypeDef huart1;

/* USER CODE END PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

static void printmsg(char *format,...);
static void USART1_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */
  USART1_Init();


  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  // 1. Obtener la dirección de los pesos (params) desde tu archivo de datos
  // Busca en 'stai_network_data.h' el nombre exacto de la función que termina en _get()
  // Probablemente sea 'stai_network_params_get' o 'stai_network_data_params_get'
  extern const uint8_t* stai_network_params_get(void);

  stai_ptr weights_addr = (stai_ptr)stai_network_params_get();
  stai_ptr weights_list[] = { weights_addr };
  stai_ptr activations_list[] = { (stai_ptr)activations };

  // 2. Configurar pesos y activaciones (3 argumentos cada una según tu .c)
  // Argumentos: (puntero a red, lista de punteros, cantidad de bloques)
  stai_network_set_weights(&network, weights_list, 1);
  stai_network_set_activations(&network, activations_list, 1);

  // 3. Inicializar la red (1 solo argumento según tu .c)
  stai_ret = stai_network_init(&network);

  if (stai_ret != STAI_SUCCESS) {
      printmsg("Error Init: %d\n", (int)stai_ret);
      Error_Handler();
  }

  // 4. Obtener las direcciones de los buffers de entrada/salida
  // La API pide una lista donde ESCRIBIR los punteros y una variable para el conteo
  stai_ptr input_ptrs[STAI_NETWORK_IN_NUM];
  stai_ptr output_ptrs[STAI_NETWORK_OUT_NUM];
  stai_size n_in, n_out;

  stai_network_get_inputs(&network, input_ptrs, &n_in);
  stai_network_get_outputs(&network, output_ptrs, &n_out);

  // 5. Asignar a tus variables globales para usarlas en el bucle principal
  // (Hacemos cast a stai_buffer* que es lo que espera tu código de proceso)
  ai_input  = (stai_buffer*)input_ptrs[0];
  ai_output = (stai_buffer*)output_ptrs[0];



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
static void USART1_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure GPIO pins : PE5 PE6 */
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

static void printmsg(char *format,...)
{
  char str[80];

  /*Extract the the argument list using VA apis */
  va_list args;
  va_start(args, format);
  vsprintf(str, format,args);
  HAL_UART_Transmit(&huart1,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
  va_end(args);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
