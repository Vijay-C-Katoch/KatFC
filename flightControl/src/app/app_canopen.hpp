
#include "ao_freertos.hpp"

class CanOpenAO : public FrActive {
 public:
  CanOpenAO(uint8_t taskPriority, void *taskStack, std::uint32_t taskStackSize,
            KFC::Event **qStorage, uint32_t qLen, void *const parameters);

  virtual void Dispatch(KFC::Event const *const e) override;

  virtual void EventCallback() override;

  void TestEventSend();

 private:
  FrTimer m_timer;
};