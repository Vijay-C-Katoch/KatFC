
#include "app_canopen.hpp"

#include "ao_freertos.hpp"
#include "app_active.hpp"

extern "C" {
#include "fdcan.h"
#include "tim.h"
}

void CanOpenAO::Dispatch(KFC::Event const *const e) {
  switch (e->sig) {
    case AOSignals::SIG_INIT: {
      InitCOStack();
      m_timer.Arm(10);
      // TestEventSend();
      break;
    }
    case AppSignals::CO_TIMER: {
      // Reflect CANopenStatus on LEDs
      GPIO_PinState ledGreen =
          static_cast<GPIO_PinState>(!m_canOpenNodeSTM32.outStatusLEDGreen);
      GPIO_PinState ledRed =
          static_cast<GPIO_PinState>(!m_canOpenNodeSTM32.outStatusLEDRed);
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, ledGreen);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, ledRed);
      canopen_app_process();
    }
    default: {
      break;
    }
  }
}

CanOpenAO::CanOpenAO(uint8_t taskPriority, void *taskStack,
                     std::uint32_t taskStackSize, KFC::Event **qStorage,
                     uint32_t qLen, void *const parameters)
    : FrActive(taskPriority, taskStack, taskStackSize, qStorage, qLen,
               parameters),
      m_timer(this, PERIODIC) {}

void CanOpenAO::EventCallback() {
  static KFC::Event coEvent{AppSignals::CO_TIMER};
  Post(&coEvent);
}

/* Test function . Remove later*/
void CanOpenAO::TestEventSend() {
  static KFC::Event se = KFC::Event(AppSignals::CO_TIMER);

  // Send 4 dummy events to queue
  for (uint8_t i = 0; i < 4; i++) {
    this->Post(&se);
  }
}

void CanOpenAO::InitCOStack() {
  m_canOpenNodeSTM32.CANHandle = &hfdcan1;
  m_canOpenNodeSTM32.HWInitFunction = MX_FDCAN1_Init;
  m_canOpenNodeSTM32.timerHandle = &htim17;
  m_canOpenNodeSTM32.desiredNodeID = 21;
  m_canOpenNodeSTM32.baudrate = 125;
  canopen_app_init(&m_canOpenNodeSTM32);
}