/** @file freertos_ao.hpp
 * @brief Active Object interface layer over FreeRTOS.
 */

#ifndef _FREERTOS_AO_H_
#define _FREERTOS_AO_H_

/* KatFC includes */
#include "kfacore.hpp"

/* FreeRTOS includes*/
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"

/** @enum AOSignals
 * @brief Active Object signals
 */
enum AOSignals : KFC::Signal {
  SIG_INIT, /**< Init signal, first signal sent to active object  */
  SIG_USR   /**< User Signal */
};

typedef enum {
  ONE_SHOT = pdFALSE, /**< One-shot timer */
  PERIODIC = pdTRUE   /**< Periodic timer */
} TimerType_t;

class FrActive : public KFC::Active {
 public:
  FrActive(std::uint8_t taskPriority, void *taskStack,
           std::uint32_t taskStackSize, KFC::Event **qStorage,
           std::uint32_t qLen, void *const parameters);

  void Post(KFC::Event const *const e) override;

  void PostFromISR(KFC::Event const *const e,
                   BaseType_t *pxHigherPriorityTaskWoken);

  // virtual void Dispatch(KFC::Event const *const e) override;

  virtual ~FrActive() {}

 private:
  FrActive(const FrActive &) = delete;

  static void Run(void *pvParameters);

  static constexpr KFC::Event initEvt{SIG_INIT};

  TaskHandle_t thread;   /**< private thread of active object */
  StaticTask_t threadCB; /**< static allocated thread control block */
  QueueHandle_t queue;   /**< event queue */
  StaticQueue_t queueCB; /**< static allocated queue control block */
};

class FrTimeEvent : public KFC::TimerEvent {
 public:
  FrTimeEvent(KFC::Signal s, KFC::Active *act, TimerType_t typ);

  virtual void Arm(uint32_t ms) override;

  virtual void Disarm() override;

  StaticTimer_t timer_cb; /**< static allocated timer control block */
  static void TimeEvent_callback(TimerHandle_t xTimer);

 private:
  KFC::Active *ao;     /**< Associated Active object */
  TimerType_t type;    /**< periodic or one-shot timer*/
  TimerHandle_t timer; /**< timer handle */
};

#endif /* _FREERTOS_AO_H_ */
