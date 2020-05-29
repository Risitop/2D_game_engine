#include <iostream>

#include "../inc/GameEngine.hpp"

typedef unsigned int EntityID;

int main() {
  GameEngine g;
  g.initialize("");
  g.main_loop();
  return 0;
}
