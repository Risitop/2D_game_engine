#pragma once

#include "System.hpp"

class InputSystem : System {
 public:
  //! Default constructor
  InputSystem();

  //! Copy constructor
  InputSystem(const InputSystem &other);

  //! Move constructor
  InputSystem(InputSystem &&other) noexcept;

  //! Destructor
  virtual ~InputSystem() noexcept;

  //! Copy assignment operator
  InputSystem &operator=(const InputSystem &other);

  //! Move assignment operator
  InputSystem &operator=(InputSystem &&other) noexcept;

 protected:
 private:
};
