#pragma once

#include "MotionComponent.hpp"
#include "System.hpp"
#include "TransformComponent.hpp"

class PhysicsSystemEntity : public SystemEntity {
  friend class PhysicsSystem;
 public:
  //! Default constructor
  PhysicsSystemEntity(MotionComponent *motion, TransformComponent *transform)
      : m_motion(motion), m_transform(transform) {}

  //! Copy constructor
  PhysicsSystemEntity(const PhysicsSystemEntity &other) = delete;

  //! Move constructor
  PhysicsSystemEntity(PhysicsSystemEntity &&other) noexcept
      : m_motion(other.m_motion), m_transform(other.m_transform) {}

  //! Destructor
  virtual ~PhysicsSystemEntity() noexcept {}

  //! Copy assignment operator
  PhysicsSystemEntity &operator=(const PhysicsSystemEntity &other) = delete;

  //! Move assignment operator
  PhysicsSystemEntity &operator=(PhysicsSystemEntity &&other) noexcept {
    m_motion = other.m_motion;
    m_transform = other.m_transform;
    return *this;
  }

 protected:
 private:
  MotionComponent *m_motion;
  TransformComponent *m_transform;
};

class PhysicsSystem : public System {
 public:
  //! Default constructor
  PhysicsSystem();

  //! Copy constructor
  PhysicsSystem(const PhysicsSystem &other) = delete;

  //! Move constructor
  PhysicsSystem(PhysicsSystem &&other) noexcept = delete;

  //! Destructor
  virtual ~PhysicsSystem() noexcept;

  //! Copy assignment operator
  PhysicsSystem &operator=(const PhysicsSystem &other) = delete;

  //! Move assignment operator
  PhysicsSystem &operator=(PhysicsSystem &&other) noexcept = delete;

  virtual bool addEntity(std::vector<Component *> entity);
  virtual void update(sf::Time dt);

 protected:
 private:
  std::vector<PhysicsSystemEntity> m_entities;
  Vector2D<float> m_gravity;
};
