#pragma once

#include <map>
#include <vector>

#include "Application.hpp"

using namespace std;
using namespace sf;

struct KeyState {
  Keyboard::Key key;
  char state;  // 00000dpr, down-pressed-released
};

class EventHandler {
 public:
  EventHandler(Application* application);
  ~EventHandler();

  void listenEvents();

  bool closed();

  bool keyDown(const Keyboard::Key& key);
  bool keyPressed(const Keyboard::Key& key);
  bool keyReleased(const Keyboard::Key& key);

 private:
  map<Keyboard::Key, KeyState> m_keystates;
  bool m_closed;  // Close window button pushed

  void m_apply(char mask);
  Application* m_application;
};
