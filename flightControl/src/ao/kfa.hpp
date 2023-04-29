/** @file kfa.hpp
 * @brief KatFC interface for active Objects and state machine.
 */

#ifndef _KFA_HPP_
#define _KFA_HPP_

namespace KFC {

/** @defgroup ao Active Object Interface
 *  Active Object interface layer over FreeRTOS
 *  @{
 */

using Signal = std::uint16_t;

/**
 * @brief Event class without parameters and serve as base class for
 * events
 */
class Event {
 public:
  Signal sig;

 public:
  constexpr Event(Signal s) : sig(s) {}
};

/**
 * @brief Base Class for Active Objects
 */
class Active {
 public:
  virtual void Dispatch(Event const* const e) = 0;
  virtual void Post(KFC::Event const* const e) = 0;
  virtual void EventCallback() = 0;
};

/**
 * @brief Base Class for Timer
 */
class Timer {
 public:
  virtual void Arm(std::uint32_t ms) = 0;
  virtual void Disarm() = 0;
};

} /* namespace KFC */

/** @} */  // end of group ao

#endif /* _KFA_HPP_ */
