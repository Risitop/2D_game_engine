#include "../inc/EntityHandler.hpp"

EntityHandler::EntityHandler(lua_State* L) : m_lua_state(L) {}

EntityHandler::~EntityHandler() noexcept {
  std::cout << "Entity handler destructor."
            << "\n";
  std::map<EntityID, Entity*>::iterator it;
  for (it = m_map.begin(); it != m_map.end(); it++) {
    std::cout << "Removing entity " << it->second->id << "\n";
    removeEntity(it->second->id);
  }
}

EntityID EntityHandler::addEntity(luabridge::LuaRef& object) {
  Entity* entity = new Entity();
  EntityID new_id = m_map.insert(entity);
  entity->id = new_id;
  entity->active = true;
  object.push(m_lua_state);
  luabridge::push(m_lua_state, luabridge::Nil());

  // We extract all components and add them to the new entity
  while (lua_next(m_lua_state, -2)) {
    luabridge::LuaRef comp_type = luabridge::LuaRef::fromStack(m_lua_state, -2);
    luabridge::LuaRef comp_obj = luabridge::LuaRef::fromStack(m_lua_state, -1);
    std::string comp_type_s = comp_type.cast<std::string>();
    ComponentID comp_id =
        m_component_handler.addComponent(comp_type_s, comp_obj);
    Component* comp = m_component_handler.getComponent(comp_id);
    entity->components.push_back(comp);
    entity->component_ids.push_back(comp_id);
    lua_pop(m_lua_state, 1);
  }

  object.pop();

  return new_id;
}

Entity* EntityHandler::getEntity(EntityID id) { return m_map.get(id); }

void EntityHandler::removeEntity(EntityID id) {
  Entity* entity = getEntity(id);
  for (ComponentID& component_id : entity->component_ids) {
    std::cout << "Removing component " << component_id << "\n";
    m_component_handler.removeComponent(component_id);
  }
  m_map.remove(id);
  delete entity;
  std::cout << "Entity " << id << " removed."
            << "\n";
}
