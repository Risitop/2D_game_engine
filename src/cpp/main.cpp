#include <iostream>

#include "../inc/RenderComponent.hpp"

using namespace luabridge;

int main() {
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "assets/scripts/test_render.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);

  LuaRef comp = getGlobal(L, "RenderComponent");

  RenderComponent t(comp);
  std::cout << t << "\n";
  return 0;
}
