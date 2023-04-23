
#include "ao_freertos.hpp"
#include "app_active.hpp"

class CanOpenAO : public FrActive {
 public:
  CanOpenAO(uint8_t taskPriority, void *taskStack, std::uint32_t taskStackSize,
            KFC::Event **qStorage, uint32_t qLen, void *const parameters)
      : FrActive(taskPriority, taskStack, taskStackSize, qStorage, qLen,
                 parameters),
        m_timeEvent(AppSignals::CO_TIMER, this) {}

  virtual void Dispatch(KFC::Event const *const e) override;

  void TestEventSend();

 private:
  FrTimeEvent m_timeEvent;
};