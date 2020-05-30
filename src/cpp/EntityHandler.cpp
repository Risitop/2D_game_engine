#include "../inc/EntityHandler.hpp"

EntityHandler::EntityHandler() : m_system_handler(NULL) {}

EntityHandler::~EntityHandler() noexcept {
  std::map<EntityID, Entity*>::iterator it;
  for (it = m_map.begin(); it != m_map.end(); it++) {
    freeEntity(it->second->id);
  }
}

EntityID EntityHandler::addEntity(luabridge::LuaRef& object) {
  assert(m_system_handler != NULL);
  lua_State* lua_state = object.state();
  Entity* entity = new Entity();
  EntityID new_id = m_map.insert(entity);
  entity->id = new_id;
  entity->active = true;
  object.push(lua_state);
  luabridge::push(lua_state, luabridge::Nil());

  // We extract all components and add them to the new entity
  while (lua_next(lua_state, -2)) {
    luabridge::LuaRef comp_type = luabridge::LuaRef::fromStack(lua_state, -2);
    luabridge::LuaRef comp_obj = luabridge::LuaRef::fromStack(lua_state, -1);
    std::string comp_type_s = comp_type.cast<std::string>();
    ComponentID comp_id =
        m_component_handler.addComponent(comp_type_s, comp_obj);
    Component* comp = m_component_handler.getComponent(comp_id);
    entity->components.push_back(comp);
    entity->component_ids.push_back(comp_id);
    lua_pop(lua_state, 1);
  }

  object.pop();

  m_system_handler->addEntity(entity->components);

  return new_id;
}

Entity* EntityHandler::getEntity(EntityID id) { return m_map.get(id); }

void EntityHandler::removeEntity(EntityID id) {
  m_map.remove(id);
  freeEntity(id);
}

void EntityHandler::freeEntity(EntityID id) {
  Entity* entity = getEntity(id);
  for (ComponentID& component_id : entity->component_ids) {
    m_component_handler.removeComponent(component_id);
  }
  delete entity;
}
