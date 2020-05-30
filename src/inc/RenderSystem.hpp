#pragma once

#include "AnimatedComponent.hpp"
#include "RenderComponent.hpp"
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
  RenderSystemEntity(const RenderSystemEntity &other);

  //! Move constructor
  RenderSystemEntity(RenderSystemEntity &&other) noexcept = delete;

  //! Destructor
  virtual ~RenderSystemEntity() noexcept {}

  //! Copy assignment operator
  RenderSystemEntity &operator=(const RenderSystemEntity &other) = delete;

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
  virtual void update();

 protected:
 private:
  std::vector<RenderSystemEntity *> m_entities;
};
