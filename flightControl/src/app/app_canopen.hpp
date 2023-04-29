/** @file app_canopen.hpp
 * @brief CANopen Active Object event generation interface
 */

#ifndef _APP_CANOPEN_HPP_
#define _APP_CANOPEN_HPP_

#include "ao_freertos.hpp"
extern "C" {
#include "CO_app_STM32.h"
}

/**
 * @brief CANopen class to send and process event
 *
 */
class CanOpenAO : public FrActive {
 public:
  /**
   * @brief CanOpenAO class constructor for Active CANopen object
   *
   * @param taskPriority task priority
   * @param taskStack  pointer to statically allocated stack for task
   * @param taskStackSize  size of provided statically allocated stack
   * @param qStorage  pointer to statically allocated array of Event pointers
   * @param qLen  size of provided statically allocated array of Event pointers
   * @param parameters  parameters for construction
   */
  CanOpenAO(uint8_t taskPriority, void *taskStack, std::uint32_t taskStackSize,
            KFC::Event **qStorage, uint32_t qLen, void *const parameters);

  /**
   * @brief Event processing function where Event is dispatched from Active
   * Object Run function
   *
   * @param e Event dispatched from this Active Object Run function
   */
  virtual void Dispatch(KFC::Event const *const e) override;

  /** @brief Callback function invoked when Event is to be Posted */
  virtual void EventCallback() override;

 private:
  /* non copyable*/
  CanOpenAO(const CanOpenAO &) = delete;
  CanOpenAO &operator=(const CanOpenAO &) = delete;

  /** @brief Initialize CANopen stack */
  void InitCOStack();
  FrTimer m_timer;                     /**< FreeRTOS Timer */
  CANopenNodeSTM32 m_canOpenNodeSTM32; /**< CANopen  node */
};

#endif /* _APP_CANOPEN_HPP_ */