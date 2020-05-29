#pragma once

typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

class ComponentHandler;

/*
 * This is the common interface to all components.
 */
class Component {
  friend class ComponentHandler;

 public:
  static const ComponentType ID;

  //! Default constructor
  Component() : m_id(0) {}

  //! Copy constructor
  Component(const Component &other) {}

  //! Move constructor
  Component(Component &&other) noexcept = delete;

  //! Lua constructor
  Component(luabridge::LuaRef &object) {}

  //! Destructor
  virtual ~Component() noexcept {};

  //! Copy assignment operator
  Component &operator=(const Component &other) = delete;

  //! Move assignment operator
  Component &operator=(Component &&other) noexcept = delete;

  //! Load
  void loadFromLua(luabridge::LuaRef &object) {}

  ComponentID id() { return m_id; }

 protected:
  void setId(ComponentID id) { m_id = id; }

 private:
  ComponentID m_id;
};

std::ostream &operator<<(std::ostream &stream, const Component &component);
