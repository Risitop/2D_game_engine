#pragma once

#include "ComponentHandler.hpp"
#include "SmartMap.hpp"

typedef unsigned int EntityID;

struct Entity {
  EntityID id;
  bool active;
  std::vector<Component *> components;
  std::vector<ComponentID> component_ids;
};

class EntityHandler {
 public:
  //! Default constructor
  EntityHandler();

  //! Copy constructor
  EntityHandler(const EntityHandler &other) = delete;

  //! Move constructor
  EntityHandler(EntityHandler &&other) noexcept = delete;

  //! Destructor
  virtual ~EntityHandler() noexcept;

  //! Copy assignment operator
  EntityHandler &operator=(const EntityHandler &other) = delete;

  //! Move assignment operator
  EntityHandler &operator=(EntityHandler &&other) noexcept = delete;

  EntityID addEntity(luabridge::LuaRef &object);
  Entity *getEntity(EntityID id);
  void removeEntity(EntityID id);

 protected:
 private:
  SmartMap<EntityID, Entity *> m_map;
  ComponentHandler m_component_handler;
  void freeEntity(EntityID id);
};
