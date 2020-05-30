#include "../inc/RenderSystem.hpp"

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() noexcept {
  for (RenderSystemEntity* entity : m_entities) {
    delete entity;
  }
}

bool RenderSystem::addEntity(std::vector<Component*> entity) {
  AnimatedComponent* animated = NULL;
  RenderComponent* render = NULL;
  TransformComponent* transform = NULL;

  for (Component* component : entity) {
    AnimatedComponent* tmp_a = dynamic_cast<AnimatedComponent*>(component);
    if (tmp_a != nullptr) {
      animated = tmp_a;
      continue;
    }

    RenderComponent* tmp_r = dynamic_cast<RenderComponent*>(component);
    if (tmp_r != nullptr) {
      render = tmp_r;
      continue;
    }

    TransformComponent* tmp_t = dynamic_cast<TransformComponent*>(component);
    if (tmp_t != nullptr) {
      transform = tmp_t;
      continue;
    }
  }

  if (transform != NULL && render != NULL) {
    m_entities.push_back(new RenderSystemEntity(render, transform, animated));
    std::cout << "Render entity added."
              << "\n";
    return true;
  }

  return false;
}

void RenderSystem::update() {}
