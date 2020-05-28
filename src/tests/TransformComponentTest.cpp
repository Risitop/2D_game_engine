#include <iostream>

#include "../inc/TransformComponent.hpp"

using namespace luabridge;

int main() {
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "assets/scripts/test_transform.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);

  LuaRef comp = getGlobal(L, "TransformComponent");

  TransformComponent t(comp);
  std::cout << t << "\n";
  t.scale(Vector2D(2, 2));
  std::cout << t << "\n";
  return 0;
}
