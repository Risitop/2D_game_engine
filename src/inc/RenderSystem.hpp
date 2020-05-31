#pragma once

#include <SFML/Graphics/VertexArray.hpp>

#include "AnimatedComponent.hpp"
#include "RenderComponent.hpp"
#include "ServiceLocator.hpp"
#include "System.hpp"
#include "TransformComponent.hpp"

class RenderSystemEntity : public SystemEntity {
  friend class RenderSystem;

 public:
  //! Default constructor
  RenderSystemEntity(RenderComponent *render, TransformComponent *transform,
                     AnimatedComponent *animated = NULL)
      : m_render(render), m_transform(transform), m_animated(animated) {}

  //! Copy constructor
  RenderSystemEntity(const RenderSystemEntity &other)
      : m_render(other.m_render),
        m_transform(other.m_transform),
        m_animated(other.m_animated) {}

  //! Move constructor
  RenderSystemEntity(RenderSystemEntity &&other) noexcept = delete;

  //! Destructor
  virtual ~RenderSystemEntity() noexcept {}

  //! Copy assignment operator
  RenderSystemEntity &operator=(const RenderSystemEntity &other) {
    m_render = other.m_render;
    m_transform = other.m_transform;
    m_animated = other.m_animated;
    return *this;
  }

  //! Move assignment operator
  RenderSystemEntity &operator=(RenderSystemEntity &&other) noexcept = delete;

  bool isAnimated() { return m_animated != NULL; }

 protected:
 private:
  RenderComponent *m_render;
  TransformComponent *m_transform;
  AnimatedComponent *m_animated;
};

class RenderSystem : public System {
 public:
  //! Default constructor
  RenderSystem();

  //! Copy constructor
  RenderSystem(const RenderSystem &other);

  //! Move constructor
  RenderSystem(RenderSystem &&other) noexcept;

  //! Destructor
  virtual ~RenderSystem() noexcept;

  //! Copy assignment operator
  RenderSystem &operator=(const RenderSystem &other);

  //! Move assignment operator
  RenderSystem &operator=(RenderSystem &&other) noexcept;

  virtual bool addEntity(std::vector<Component *> entity);
  virtual void update(sf::Time dt);

 protected:
 private:
  std::vector<RenderSystemEntity> m_entities;
  sf::VertexArray m_vertex_array;

  void insertSortedEntity(const RenderSystemEntity &entity);
  void addEntityVertices(const RenderSystemEntity &entity);
};
