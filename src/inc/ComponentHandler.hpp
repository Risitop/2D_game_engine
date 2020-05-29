#pragma once

#include <vector>

#include "AnimatedComponent.hpp"
#include "RenderComponent.hpp"
#include "SmartMap.hpp"
#include "TransformComponent.hpp"

typedef unsigned int ComponentID;
struct ComponentPosition {
  size_t type;
  size_t index;
};

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

  //! Creates a new component, releases an ID
  ComponentID addComponent(std::string comp_type, luabridge::LuaRef &object) {
    ComponentType type = m_s2c[comp_type];  // Converts type into ComponentID
    checkComponentType(type);
    Component *component;

    // Creates a new component
    switch (type) {
      case AnimatedComponent::ID:
        component = new AnimatedComponent(object);
        break;
      case RenderComponent::ID:
        component = new RenderComponent(object);
        break;
      case TransformComponent::ID:
        component = new TransformComponent(object);
        break;
      default:
        throw "Unkown component type.";
        break;
    }

    // Saves the position, generates the ID
    ComponentID index = m_components[type]->insert(component);
    ComponentPosition *pos = new ComponentPosition;
    pos->type = type;
    pos->index = index;
    return m_comp_pos.insert(pos);
  }

  //! Gets a component by ID
  Component *getComponent(ComponentID id) {
    ComponentPosition pos = *m_comp_pos.get(id);    // Retrieving the position
    return m_components[pos.type]->get(pos.index);  // Retrieving the address
  }

  //! Removes a component by ID
  void removeComponent(ComponentID id) {
    ComponentPosition pos = *m_comp_pos.get(id);  // Retrieving the position
    Component *component =
        m_components[pos.type]->get(pos.index);  // Retrieving the address
    m_components[pos.type]->remove(pos.index);   // Freeing the index
    delete component;                            // Freeing the memory
  }

 protected:
 private:
  std::vector<SmartMap<ComponentID, Component *> *> m_components;

  // Checks if the vector is big enough to store the ComponentType.
  // Else, extends it.
  void checkComponentType(ComponentType type);
  std::map<std::string, ComponentType>
      m_s2c;  // Maps component name to component type ID
  SmartMap<ComponentID, ComponentPosition *> m_comp_pos;
};
