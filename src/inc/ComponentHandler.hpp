#pragma once

#include <vector>

#include "AnimatedComponent.hpp"
#include "Component.hpp"

class ComponentHandler {
 public:
  //! Default constructor
  ComponentHandler();

  //! Copy constructor
  ComponentHandler(const ComponentHandler &other) = delete;

  //! Move constructor
  ComponentHandler(ComponentHandler &&other) noexcept = delete;

  //! Destructor
  virtual ~ComponentHandler() noexcept;

  //! Copy assignment operator
  ComponentHandler &operator=(const ComponentHandler &other) = delete;

  //! Move assignment operator
  ComponentHandler &operator=(ComponentHandler &&other) noexcept = delete;

  //! Creates a new component
  template <class TypeComponent>
  TypeComponent *addComponent(luabridge::LuaRef &object) {
    checkComponentType(TypeComponent::ID);
    TypeComponent *component = new TypeComponent(object);
    m_components[TypeComponent::ID]->push_back(component);
    return component;
  }

 protected:
 private:
  std::vector<std::vector<Component *> *> m_components;
  void checkComponentType(ComponentType type);
};
