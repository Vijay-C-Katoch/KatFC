
#include "ao_freertos.hpp"
extern "C" {
#include "CO_app_STM32.h"
}

class CanOpenAO : public FrActive {
 public:
  CanOpenAO(uint8_t taskPriority, void *taskStack, std::uint32_t taskStackSize,
            KFC::Event **qStorage, uint32_t qLen, void *const parameters);

  virtual void Dispatch(KFC::Event const *const e) override;

  virtual void EventCallback() override;

  // Test function
  void TestEventSend();

 private:
  void InitCOStack();
  FrTimer m_timer;
  CANopenNodeSTM32 m_canOpenNodeSTM32;
};