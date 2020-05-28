#include <iostream>

#include "../inc/SmartMap.hpp"

typedef unsigned int EntityID;

int main() {
  SmartMap<EntityID, int> s;
  s.insert(0);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.remove(3);
  s.remove(1);
  s.insert(5);
  s.insert(6);

  std::map<EntityID, int>::iterator it;
  for (it = s.begin(); it != s.end(); it++) {
    std::cout << it->first << "->" << it->second << "\n";
  }

  return 0;
}
