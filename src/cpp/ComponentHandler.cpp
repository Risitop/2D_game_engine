#include "../inc/ComponentHandler.hpp"

ComponentHandler::ComponentHandler() {
  // Initializing the lookup table
  m_s2c["AnimatedComponent"] = AnimatedComponent::ID;
  m_s2c["RenderComponent"] = RenderComponent::ID;
  m_s2c["TransformComponent"] = TransformComponent::ID;
  m_s2c["MotionComponent"] = MotionComponent::ID;
}

ComponentHandler::~ComponentHandler() noexcept {
  for (size_t id = 0; id < m_components.size(); id++) {
    SmartMap<ComponentID, Component*>* map_components = m_components[id];
    std::map<ComponentID, Component*>::iterator it;
    for (it = map_components->begin(); it != map_components->end(); it++) {
      delete it->second;
    }
    delete map_components;
  }

  std::map<ComponentID, ComponentPosition*>::iterator it;
  for (it = m_comp_pos.begin(); it != m_comp_pos.end(); it++) {
    delete it->second;
  }
}

void ComponentHandler::checkComponentType(ComponentType type) {
  while (m_components.size() <= type) {
    SmartMap<ComponentID, Component*>* arr =
        new SmartMap<ComponentID, Component*>;
    m_components.push_back(arr);
  }
}
