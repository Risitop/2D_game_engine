#include <iostream>

#include "../inc/GameEngine.hpp"

typedef unsigned int EntityID;

int main() {
  GameEngine ge;
  ge.initialize("init.lua");
  ge.main_loop();

  return 0;
}
