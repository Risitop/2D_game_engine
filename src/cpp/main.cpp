#include <iostream>

#include "../inc/AnimatedComponent.hpp"

using namespace luabridge;

int main() {
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "assets/scripts/test_animated.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);

  LuaRef comp = getGlobal(L, "AnimatedComponent");

  AnimatedComponent t(comp);
  std::cout << t << "\n";
  return 0;
}
