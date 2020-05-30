#include "../inc/EventHandler.hpp"

#include <iostream>
#include <iterator>

#define RESET_PR 0x04
#define KEY_PRESSED 0x06
#define KEY_RELEASED 0x01
#define MASK_D 0x04
#define MASK_P 0x02
#define MASK_R 0x01

using namespace std;
using namespace sf;

EventHandler::EventHandler(Application* application)
    : m_closed(false), m_application(application) {}

EventHandler::~EventHandler() {}

void EventHandler::m_apply(char mask) {
  std::map<Keyboard::Key, KeyState>::iterator it;
  for (it = m_keystates.begin(); it != m_keystates.end(); it++) {
    (*it).second.state &= mask;
  }
}

void EventHandler::listenEvents() {
  // 0x00000100
  m_apply(RESET_PR);  // Resets "pressed" and "released"
  Event event;
  while (m_application->pollEvent(event)) {
    switch (event.type) {
      case Event::Closed:
        m_closed = true;
        break;

      case Event::KeyPressed: {
        Keyboard::Key code = event.key.code;
        if (keyDown(code)) break;  // Avoids multiple pressed events
        if (m_keystates.count(code) == 0) {
          m_keystates[code] = {code, 0};
        }
        m_keystates[code].state =
            KEY_PRESSED;  // Sets "down" and "pressed" at true
        break;
      }

      case Event::KeyReleased: {
        Keyboard::Key code = event.key.code;
        if (m_keystates.count(code) == 0) {
          m_keystates[code] = {code, 0};
        }
        m_keystates[code].state =
            KEY_RELEASED;  // Sets "released" at true, "down" and "pressed" at
                           // false
        break;
      }

      default:
        break;
    }
  }
}

bool EventHandler::closed() { return m_closed; }

bool EventHandler::keyDown(const Keyboard::Key& key) {
  if (m_keystates.count(key) == 0) {
    return false;
  }
  return ((m_keystates[key].state & MASK_D) > 0);
}

bool EventHandler::keyPressed(const Keyboard::Key& key) {
  if (m_keystates.count(key) == 0) {
    return false;
  }
  return ((m_keystates[key].state & MASK_P) > 0);
}

bool EventHandler::keyReleased(const Keyboard::Key& key) {
  if (m_keystates.count(key) == 0) {
    return false;
  }
  return ((m_keystates[key].state & MASK_R) > 0);
}
