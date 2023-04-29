/** @file main.cpp
 * @brief Application main.
 */

#include "app_canopen.hpp"
#include "bsp.hpp"
extern "C" {
#include "CO_app_STM32.h"
#include "fdcan.h"
#include "gpio.h"
#include "tim.h"
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN1_Init();
  MX_TIM17_Init();

  /* Statically allocated task stack for CANopen Active object task */
  static StackType_t co_stack[configMINIMAL_STACK_SIZE];
  /* Statically allocated queue storage for CANOpen events */
  static KFC::Event *co_queue[10];

  /* CANopen Active Object */
  CanOpenAO co(1U, co_stack, sizeof(co_stack), co_queue,
               sizeof(co_queue) / sizeof(co_queue[0]), 0);

  vTaskStartScheduler(); /* start the FreeRTOS scheduler... */
  /* Should not reach here. */
  for (;;)
    ;
  return 0; /* NOTE: the scheduler does NOT return */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
extern "C" {
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
    HAL_IncTick();
  }

  /* Handle CANopen app interrupts */
  if (htim == &htim17) {
    canopen_app_interrupt();
  }
}
}  // extern C
