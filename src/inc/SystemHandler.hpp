#pragma once

#include <vector>

#include "Component.hpp"
#include "RenderSystem.hpp"

class SystemHandler {
 public:
  //! Default constructor
  SystemHandler() { m_systems.push_back(new RenderSystem()); }

  //! Copy constructor
  SystemHandler(const SystemHandler &other) = delete;

  //! Move constructor
  SystemHandler(SystemHandler &&other) noexcept = delete;

  //! Destructor
  virtual ~SystemHandler() noexcept {
    for (System *system : m_systems) {
      delete system;
    }
  }

  //! Copy assignment operator
  SystemHandler &operator=(const SystemHandler &other) = delete;

  //! Move assignment operator
  SystemHandler &operator=(SystemHandler &&other) noexcept = delete;

  void addEntity(std::vector<Component *> entity) {
    for (System *system : m_systems) {
      system->addEntity(entity);
    }
  };
  void update() {
    for (System *system : m_systems) {
      system->update();
    }
  }

 protected:
 private:
  std::vector<System *> m_systems;
};
