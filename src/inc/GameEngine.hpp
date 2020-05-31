#pragma once

#include <SFML/System/Clock.hpp>

#include "Application.hpp"
#include "EntityHandler.hpp"
#include "EventHandler.hpp"
#include "ServiceLocator.hpp"
#include "SystemHandler.hpp"

class GameEngine {
 public:
  //! Default constructor
  GameEngine();

  //! Copy constructor
  GameEngine(const GameEngine &other) = delete;

  //! Move constructor
  GameEngine(GameEngine &&other) noexcept = delete;

  //! Destructor
  virtual ~GameEngine() noexcept;

  //! Copy assignment operator
  GameEngine &operator=(const GameEngine &other) = delete;

  //! Move assignment operator
  GameEngine &operator=(GameEngine &&other) noexcept = delete;

  void initialize(const std::string &config_path);
  int main_loop();

 protected:
 private:
  Application m_application;
  EventHandler m_event_handler;
  TextureHandler m_texture_handler;
  EntityHandler m_entity_handler;
  SystemHandler m_system_handler;
  FileManager m_file_manager;
  lua_State *m_lua_state;
};
