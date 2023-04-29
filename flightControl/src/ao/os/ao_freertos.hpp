/** @file ao_freertos.hpp
 * @brief Active Object interface layer over FreeRTOS.
 */

#ifndef _AO_FREERTOS_HPP_
#define _AO_FREERTOS_HPP_

/* KatFC includes */
#include "kfacore.hpp"

/* FreeRTOS includes*/
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"

/** @defgroup os OS Layer
 *  Active Object interface layer over FreeRTOS
 *  @{
 */

/** @enum AOSignals
 * @brief Active Object signals
 */
enum AOSignals : KFC::Signal {
  SIG_INIT, /**< Init signal, first signal sent to active object  */
  SIG_USR   /**< User Signal */
};

/** @enum TimerType_t
 * @brief FreeRTOS Timer types
 */
typedef enum {
  ONE_SHOT = pdFALSE, /**< One-shot timer */
  PERIODIC = pdTRUE   /**< Periodic timer */
} TimerType_t;

/**
 * @brief Class for Active Object using FreeRTOS
 *
 */
class FrActive : public KFC::Active {
 public:
  /**
   * @brief FrActive class constructor for statically allocated task and queue
   *
   * @param taskPriority priority of FreeRTOS task
   * @param taskStack  pointer to statically allocated stack for task
   * @param taskStackSize  size of provided statically allocated stack
   * @param qStorage  pointer to statically allocated array of Event pointers
   * @param qLen  size of provided statically allocated array of Event pointers
   * @param parameters  parameters for construction
   */
  FrActive(std::uint8_t taskPriority, void *taskStack,
           std::uint32_t taskStackSize, KFC::Event **qStorage,
           std::uint32_t qLen, void *const parameters);

  /**
   * @brief Post events to active object queue
   *
   * @param e Event to send
   */
  void Post(KFC::Event const *const e) override;

  /**
   * @brief Post events from ISR to active object queue
   *
   * @param e Event to post
   * @param pxHigherPriorityTaskWoken pdTRUE to unblock high priority task else
   *        pdFALSE
   */
  void PostFromISR(KFC::Event const *const e,
                   BaseType_t *pxHigherPriorityTaskWoken);

  virtual ~FrActive() {}

 private:
  FrActive(const FrActive &) = delete;

  /** Active Object Private Run member function **/
  static void Run(void *pvParameters);

  /** initial event signal */
  static constexpr KFC::Event initEvt{SIG_INIT};

  QueueHandle_t queue;   /**< event queue */
  StaticQueue_t queueCB; /**< static allocated queue control block */
  TaskHandle_t thread;   /**< private thread of active object */
  StaticTask_t threadCB; /**< static allocated thread control block */
};

/**
 * @brief Timer class using FreeRTOS for time events
 *
 */
class FrTimer : public KFC::Timer {
 public:
  /**
   * @brief FrTimer class constructor for FreeRTOS static timer
   * @param act pointer to active object to send event to
   * @param typ FreeRTOS timer type periodic or one-shot
   */
  FrTimer(KFC::Active *act, TimerType_t typ);

  /**
   * @brief Arm timer
   *
   * @param ms Timer timeout count in milliseconds
   */
  virtual void Arm(uint32_t ms) override;

  /** @brief Disarm timer */
  virtual void Disarm() override;

  /** @brief Callback function on timeout */
  static void TimerCallback(TimerHandle_t xTimer);

 private:
  KFC::Active *ao;               /**< Associated Active object */
  TimerType_t type;              /**< periodic or one-shot timer*/
  static StaticTimer_t timer_cb; /**< static allocated timer control block */
  static TimerHandle_t timer;    /**< timer handle */
};

/** @} */  // end of group os

#endif /* _AO_FREERTOS_HPP_ */
