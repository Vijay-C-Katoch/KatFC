/** @file kfa.hpp
 * @brief KatFC interface for active Objects and state machine.
 */

#ifndef _KFA_H_
#define _KFA_H_

namespace KFC {

using Signal = std::uint16_t;

/**
 * @brief Event class without parameters and serve as base class for
 * events
 *
 */
class Event {
 public:
  Signal sig;

 public:
  constexpr Event(Signal s) : sig(s) {}
};

class Active {
 public:
  virtual void Dispatch(Event const* const e) = 0;
  virtual void Post(KFC::Event const* const e) = 0;
  virtual void EventCallback() = 0;
};

class Timer {
 public:
  virtual void Arm(std::uint32_t ms) = 0;

  virtual void Disarm() = 0;
};

} /* namespace KFC */

#endif /* _KFA_H_ */
