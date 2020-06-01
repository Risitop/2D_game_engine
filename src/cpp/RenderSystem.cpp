#include "../inc/RenderSystem.hpp"

RenderSystem::RenderSystem() { m_vertex_array.setPrimitiveType(sf::Quads); }

RenderSystem::~RenderSystem() noexcept {}

bool RenderSystem::addEntity(std::vector<Component*> entity) {
  AnimatedComponent* animated = nullptr;
  RenderComponent* render = nullptr;
  TransformComponent* transform = nullptr;

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

  if (transform != nullptr && render != nullptr) {
    RenderSystemEntity render_entity(render, transform, animated);
    insertSortedEntity(std::move(render_entity));
    std::cout << "Render entity added."
              << "\n";
    return true;
  }

  return false;
}

void RenderSystem::update(sf::Time dt) {
  m_vertex_array.clear();
  Application* app = ServiceLocator::App();
  sf::RenderStates states;

  // Custom batching
  // m_entities must be ordered by z-order
  states.texture = nullptr;
  for (RenderSystemEntity& entity : m_entities) {
    sf::Texture* e_tex = entity.m_render->getTexture();

    if (entity.isAnimated()) {
      entity.m_animated->update(dt);
      entity.m_render->setFrame(entity.m_animated->frame());
    }

    if (e_tex != states.texture) {
      // Render
      app->draw(m_vertex_array, states);
      m_vertex_array.clear();
      states.texture = e_tex;
    }
    addEntityVertices(entity);
  }
  app->draw(m_vertex_array, states);
}

void RenderSystem::insertSortedEntity(RenderSystemEntity&& entity) {
  int zindex = entity.m_render->zIndex();
  m_entities.push_back(std::move(entity));
  size_t pos = m_entities.size() - 1;
  while (pos > 0 && m_entities[pos - 1].m_render->zIndex() > zindex) {
    m_entities[pos] = m_entities[pos - 1];
    pos--;
  }
  m_entities[pos] = entity;
}

void RenderSystem::addEntityVertices(const RenderSystemEntity& entity) {
  sf::IntRect frame = entity.m_render->getFrame();
  sf::Vertex vertices[4];
  entity.m_transform->getVertices(frame, vertices);

  sf::Vertex v00 = vertices[0];
  v00.texCoords = sf::Vector2f(frame.left, frame.top);
  m_vertex_array.append(v00);

  sf::Vertex v10 = vertices[1];
  v10.texCoords = sf::Vector2f(frame.left + frame.width, frame.top);
  m_vertex_array.append(v10);

  sf::Vertex v01 = vertices[2];
  v01.texCoords =
      sf::Vector2f(frame.left + frame.width, frame.top + frame.height);
  m_vertex_array.append(v01);

  sf::Vertex v11 = vertices[3];
  v11.texCoords = sf::Vector2f(frame.left, frame.top + frame.height);
  m_vertex_array.append(v11);
}
