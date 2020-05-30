#pragma once

#include "Component.hpp"

class SystemEntity {
 public:
  //! Default constructor
  SystemEntity() {}

  //! Copy constructor
  SystemEntity(const SystemEntity &other);

  //! Move constructor
  SystemEntity(SystemEntity &&other) noexcept = delete;

  //! Destructor
  virtual ~SystemEntity() noexcept {}

  //! Copy assignment operator
  SystemEntity &operator=(const SystemEntity &other) = delete;

  //! Move assignment operator
  SystemEntity &operator=(SystemEntity &&other) noexcept = delete;

 protected:
 private:
};

class System {
 public:
  //! Default constructor
  System() {}

  //! Copy constructor
  System(const System &other) = delete;

  //! Move constructor
  System(System &&other) noexcept = delete;

  //! Destructor
  virtual ~System() noexcept {}

  //! Copy assignment operator
  System &operator=(const System &other) = delete;

  //! Move assignment operator
  System &operator=(System &&other) noexcept = delete;

  virtual bool addEntity(std::vector<Component *> entity) = 0;
  virtual void update() = 0;

 protected:
 private:
};
