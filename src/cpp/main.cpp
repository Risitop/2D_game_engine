#include <iostream>

#include "../inc/AnimatedComponent.hpp"
#include "../inc/ComponentHandler.hpp"
#include "../inc/RenderComponent.hpp"
#include "../inc/TransformComponent.hpp"

using namespace luabridge;

int main() {
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "assets/scripts/test_components.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);

  LuaRef animated_obj = getGlobal(L, "AnimatedComponent");
  LuaRef render_obj = getGlobal(L, "RenderComponent");
  LuaRef transform_obj = getGlobal(L, "TransformComponent");

  ComponentHandler ch;

  std::cout << "Adding component"
            << "\n";
  AnimatedComponent* animated_comp =
      ch.addComponent<AnimatedComponent>(animated_obj);
  RenderComponent* render_comp = ch.addComponent<RenderComponent>(render_obj);
  TransformComponent* transform_comp =
      ch.addComponent<TransformComponent>(transform_obj);

  std::cout << *animated_comp << "\n";
  std::cout << *render_comp << "\n";
  std::cout << *transform_comp << "\n";
  return 0;
}
