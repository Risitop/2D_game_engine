#include "../inc/GameEngine.hpp"

GameEngine::GameEngine() {
  m_texture_handler = new TextureHandler();
  m_entity_handler = new EntityHandler();
  m_file_manager = new FileManager();
  m_lua_state = luaL_newstate();

  ServiceLocator::provide(m_file_manager);
  ServiceLocator::provide(m_texture_handler);
}

GameEngine::~GameEngine() noexcept {
  delete m_texture_handler;
  delete m_entity_handler;
  delete m_file_manager;
  lua_close(m_lua_state);
}

void GameEngine::initialize(const std::string& config_path) {
  m_texture_handler->addAtlas("assets/graphics/hero.png", 0);
}

int GameEngine::main_loop() {
  luaL_dofile(m_lua_state, "assets/entities/hero.lua");
  luaL_openlibs(m_lua_state);
  lua_pcall(m_lua_state, 0, 0, 0);
  luabridge::LuaRef entity = luabridge::getGlobal(m_lua_state, "Entity");

  std::cout << "Loading entity hero..."
            << "\n";
  EntityID e_id = m_entity_handler->addEntity(entity);

  std::cout << "Deleting EntityHandler..."
            << "\n";

  std::cout << "Program ended."
            << "\n";
  return 0;
}
