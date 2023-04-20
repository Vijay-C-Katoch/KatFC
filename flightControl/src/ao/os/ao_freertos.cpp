

#include "ao_freertos.hpp"

#include "kfacore.hpp"

using namespace std;

void FrActive::Run(void *pvParameters) {
  FrActive *me = (FrActive *)pvParameters;

  configASSERT(me); /* Active object shall be provided */

  /* initialize the AO */
  me->Dispatch(&initEvt);

  for (;;) {
    /* event is a message object */
    KFC::Event const *e;

    /* wait for events */
    xQueueReceive(me->queue, &e, portMAX_DELAY);
    configASSERT(e != (KFC::Event const *)0);

    /* dispatch event to the provided active object */
    me->Dispatch(e);
  }
}

FrActive::FrActive(uint8_t taskPriority, void *taskStack,
                   std::uint32_t taskStackSize, KFC::Event **qStorage,
                   uint32_t qLen, void *const parameters) {
  StackType_t *stkStorage = static_cast<StackType_t *>(taskStack);
  uint32_t stkDepth = (taskStackSize / sizeof(StackType_t));

  queue = xQueueCreateStatic(qLen, sizeof(KFC::Event *), (uint8_t *)qStorage,
                             &queueCB);

  configASSERT(queue);

  /** Create Active Object's private thread **/
  thread =
      xTaskCreateStatic(&Run, "AO", stkDepth, this,
                        taskPriority + tskIDLE_PRIORITY, stkStorage, &threadCB);
  configASSERT(thread);
}

void FrActive::Post(KFC::Event const *const e) {
  BaseType_t status = xQueueSend(queue, (void *)&e, (TickType_t)0);
  configASSERT(status == pdTRUE);
}

void FrActive::PostFromISR(KFC::Event const *const e,
                           BaseType_t *pxHigherPriorityTaskWoken) {
  BaseType_t status =
      xQueueSendFromISR(queue, (void *)&e, pxHigherPriorityTaskWoken);
  configASSERT(status == pdTRUE);
}

// void FrActive::Dispatch(KFC::Event const *const e) { (void)e; }

FrTimeEvent::FrTimeEvent(KFC::Signal s, FrActive *act)
    : KFC::TimerEvent(s), ao(act) {
  /* Create a timer object */
  timer =
      xTimerCreateStatic("TEv", 1U, type, this, TimeEvent_callback, &timer_cb);
  configASSERT(timer); /* timer must be created */
}

void FrTimeEvent::Arm(uint32_t ms) {
  BaseType_t status;
  TickType_t ticks;
  BaseType_t xHigherPriorityTaskWoken;

  ticks = (ms / portTICK_PERIOD_MS);
  if (0U == ticks) {
    ticks = 1U;
  }

  if (xPortIsInsideInterrupt() == pdTRUE) {
    xHigherPriorityTaskWoken = pdFALSE;

    status = xTimerChangePeriodFromISR(timer, ticks, &xHigherPriorityTaskWoken);
    configASSERT(status == pdPASS);

    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
  } else {
    status = xTimerChangePeriod(timer, ticks, 0);
    configASSERT(status == pdPASS);
  }
}

void FrTimeEvent::Disarm() {
  BaseType_t status;
  BaseType_t xHigherPriorityTaskWoken;

  if (xPortIsInsideInterrupt() == pdTRUE) {
    xHigherPriorityTaskWoken = pdFALSE;
    status = xTimerStopFromISR(timer, &xHigherPriorityTaskWoken);
    configASSERT(status == pdPASS);

    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
  } else {
    status = xTimerStop(timer, 0);
    configASSERT(status == pdPASS);
  }
}

/*..........................................................................*/

void FrTimeEvent::TimeEvent_callback(TimerHandle_t xTimer) {
  const FrTimeEvent *const time =
      static_cast<FrTimeEvent *>(pvTimerGetTimerID(xTimer));
  time->ao->Post(time);
}
