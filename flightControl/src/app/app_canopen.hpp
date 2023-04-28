
#include "ao_freertos.hpp"
#include "app_active.hpp"

class CanOpenAO : public FrActive {
 public:
  CanOpenAO(uint8_t taskPriority, void *taskStack, std::uint32_t taskStackSize,
            KFC::Event **qStorage, uint32_t qLen, void *const parameters);

  virtual void Dispatch(KFC::Event const *const e) override;

  virtual void Callback() override;

  void TestEventSend();

 private:
  FrTimeEvent m_timeEvent;
};