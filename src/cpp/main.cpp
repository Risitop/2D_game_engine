#include <iostream>

#include "../inc/EntityHandler.hpp"

typedef unsigned int EntityID;

int main() {
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "assets/scripts/test_components.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);
  luabridge::LuaRef s = luabridge::getGlobal(L, "GameObject");

  EntityHandler* eh = new EntityHandler();

  std::vector<EntityID> e_ids;
  for (int i = 0; i < 500; i++) {
    e_ids.push_back(eh->addEntity(s));
  }

  delete eh;

  lua_close(L);

  std::cout << "Program ended."
            << "\n";

  return 0;
}
