
#include "app_canopen.hpp"

#include "ao_freertos.hpp"
#include "app_active.hpp"

void CanOpenAO::Dispatch(KFC::Event const *const e) {
  switch (e->sig) {
    case AOSignals::SIG_INIT: {
      // TestEventSend();
      break;
    }
    case AppSignals::CO_TIMER: {
      std::uint8_t i = 0;

      for (; i < 10; i++) {
        std::uint8_t j = i;
        j++;
      }
    }
    default: {
      break;
    }
  }
}

void CanOpenAO::TestEventSend() {
  static KFC::Event se = KFC::Event(AppSignals::CO_TIMER);

  // Send 4 dummy events to queue
  for (uint8_t i = 0; i < 4; i++) {
    this->Post(&se);
  }
}

CanOpenAO::CanOpenAO(uint8_t taskPriority, void *taskStack,
                     std::uint32_t taskStackSize, KFC::Event **qStorage,
                     uint32_t qLen, void *const parameters)
    : FrActive(taskPriority, taskStack, taskStackSize, qStorage, qLen,
               parameters),
      m_timeEvent(AppSignals::CO_TIMER, this, PERIODIC) {
  m_timeEvent.Arm(10);
}

void CanOpenAO::Callback() { Post(&m_timeEvent); }