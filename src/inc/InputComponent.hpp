#pragma once

#include "Component.hpp"

class InputComponent : Component {
 public:
  //! Default constructor
  InputComponent();

  //! Copy constructor
  InputComponent(const InputComponent &other);

  //! Move constructor
  InputComponent(InputComponent &&other) noexcept;

  //! Destructor
  virtual ~InputComponent() noexcept;

  //! Copy assignment operator
  InputComponent &operator=(const InputComponent &other);

  //! Move assignment operator
  InputComponent &operator=(InputComponent &&other) noexcept;

 protected:
 private:
};
