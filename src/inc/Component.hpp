#pragma once

typedef unsigned int ComponentType;

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

/*
 * This is the common interface to all components.
 */
class Component {
 public:
  static const ComponentType ID;

  //! Default constructor
  Component() {}

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

 protected:
 private:
};

std::ostream &operator<<(std::ostream &stream, const Component &component);
