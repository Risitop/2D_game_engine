#include <iostream>

#include "../inc/GameEngine.hpp"

typedef unsigned int EntityID;

int main() {
  Vector2D<float> v1(12, 15);
  Vector2D<float> v2(-3, 7);
  Vector2D<float> v3(v1);

  cout << v1 << "\n";
  cout << v2 << "\n";
  cout << v1 + v2 << "\n";
  cout << v1 - v2 << "\n";
  cout << v1 * v2 << "\n";
  cout << v1 / v2 << "\n";
  cout << (v1 == v2) << "\n";
  cout << v3 << "\n";

  cout << Vector2D<float>::dot(v1, v2) << "\n";
  cout << Vector2D<float>::normalize(v1) << "\n";

  return 0;
}
