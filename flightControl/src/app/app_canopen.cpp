
#include "app_canopen.hpp"

#include "ao_freertos.hpp"
#include "app_active.hpp"

void CanOpenAO::Dispatch(KFC::Event const *const e) {
  std::uint8_t i = 0;

  for (; i < 10; i++) {
    std::uint8_t j = i;
    j++;
  }

  (void)e;
}