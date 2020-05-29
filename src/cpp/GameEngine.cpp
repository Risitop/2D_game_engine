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

void GameEngine::initialize(const std::string& config_path) {}

int GameEngine::main_loop() {
  luaL_dofile(m_lua_state, "assets/scripts/test_components.lua");
  luaL_openlibs(m_lua_state);
  lua_pcall(m_lua_state, 0, 0, 0);
  luabridge::LuaRef s = luabridge::getGlobal(m_lua_state, "GameObject");

  std::vector<EntityID> e_ids;
  for (int i = 0; i < 10; i++) {
    e_ids.push_back(m_entity_handler->addEntity(s));
  }

  std::cout << "Deleting EntityHandler..."
            << "\n";

  std::cout << "Program ended."
            << "\n";
  return 0;
}
