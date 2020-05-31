#include "../inc/GameEngine.hpp"

GameEngine::GameEngine() : m_event_handler(&m_application) {
  m_lua_state = luaL_newstate();

  m_entity_handler.provide(&m_system_handler);

  ServiceLocator::provide(&m_file_manager);
  ServiceLocator::provide(&m_texture_handler);
  ServiceLocator::provide(&m_event_handler);
  ServiceLocator::provide(&m_application);
}

GameEngine::~GameEngine() noexcept { lua_close(m_lua_state); }

void GameEngine::initialize(const std::string& config_path) {
  m_texture_handler.addAtlas("assets/graphics/hero.png", 0);
  std::cout << "Opening window..."
            << "\n";
  m_application.initialize(800, 600, "sfml");
}

int GameEngine::main_loop() {
  luaL_dofile(m_lua_state, "assets/entities/hero.lua");
  luaL_openlibs(m_lua_state);
  lua_pcall(m_lua_state, 0, 0, 0);
  luabridge::LuaRef entity = luabridge::getGlobal(m_lua_state, "Entity");

  std::cout << "Loading entity hero..."
            << "\n";
  EntityID e_id = m_entity_handler.addEntity(entity);

  sf::Clock clock;
  while (m_application.isOpen()) {
    m_event_handler.listenEvents();

    if (m_event_handler.closed()) {
      break;
    }

    sf::Time elapsed = clock.restart();
    m_system_handler.update(elapsed);

    m_application.update();
  }

  std::cout << "Deleting EntityHandler..."
            << "\n";

  std::cout << "Program ended."
            << "\n";
  return 0;
}
