/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#define ENABLE_CANOPEN_DEMO 0
#define ENABLE_FREE_RTOS 0
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "bsp.hpp"
#if ENABLE_FREE_RTOS
#include "cmsis_os.h"
#endif  // ENABLE_FREE_RTOS
#include "ao_freertos.hpp"
#include "fdcan.h"
#include "gpio.h"
#include "tim.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#if ENABLE_CANOPEN_DEMO
#include "CO_app_STM32.h"
#endif  // ENABLE_CANOPEN_DEMO
extern "C" {
#include "app_freertos.h"
}
#include "app_active.hpp"
#include "app_canopen.hpp"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN1_Init();
  MX_TIM17_Init();
  /* USER CODE BEGIN 2 */

  // Initialize the CANOpen Stack

  /* USER CODE END 2 */

#if ENABLE_FREE_RTOS
  /* Init scheduler */
  osKernelInitialize(); /* Call init function for freertos objects (in
                           freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
/* We should never get here as control is now taken by the scheduler */
#endif /* ENABLE_FREE_RTOS */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  static StackType_t co_stack[configMINIMAL_STACK_SIZE]; /* task stack */
  static KFC::Event *co_queue[10];

  CanOpenAO co(1U, co_stack, sizeof(co_stack), co_queue,
               sizeof(co_queue) / sizeof(co_queue[0]), 0);

  vTaskStartScheduler(); /* start the FreeRTOS scheduler... */
  /* Should not reach here. */
  for (;;)
    ;
  return 0; /* NOTE: the scheduler does NOT return */
  /* USER CODE END 3 */
}
