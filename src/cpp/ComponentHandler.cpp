#include "../inc/ComponentHandler.hpp"

ComponentHandler::ComponentHandler() {}

ComponentHandler::~ComponentHandler() noexcept {
  for (size_t id = 0; id < m_components.size(); id++) {
    for (size_t j = 0; j < m_components[id]->size(); j++) {
      delete (*m_components[id])[j];
    }
    delete m_components[id];
  }
}

void ComponentHandler::checkComponentType(ComponentType type) {
  while (m_components.size() <= type) {
    std::vector<Component*>* arr = new std::vector<Component*>;
    m_components.push_back(arr);
  }
}
