#include "../inc/PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem() : m_gravity(0, 0.0001) {}

PhysicsSystem::~PhysicsSystem() noexcept {}

bool PhysicsSystem::addEntity(std::vector<Component*> entity) {
  MotionComponent* motion = nullptr;
  TransformComponent* transform = nullptr;

  for (Component* component : entity) {
    MotionComponent* tmp_m = dynamic_cast<MotionComponent*>(component);
    if (tmp_m != nullptr) {
      motion = tmp_m;
      continue;
    }
    TransformComponent* tmp_t = dynamic_cast<TransformComponent*>(component);
    if (tmp_t != nullptr) {
      transform = tmp_t;
      continue;
    }
  }

  if (motion != nullptr && transform != nullptr) {
    PhysicsSystemEntity physics_entity(motion, transform);
    m_entities.push_back(std::move(physics_entity));
    std::cout << "Physics entity added."
              << "\n";
    return true;
  }

  return false;
}

void PhysicsSystem::update(sf::Time dt) {
  for (PhysicsSystemEntity& entity : m_entities) {
    float time_step = dt.asMilliseconds();
    Vector2D<float> velocity = entity.m_motion->getVelocity();
    entity.m_transform->translate(velocity * time_step);
    entity.m_motion->setVelocity(time_step);
    // entity.m_motion->addAcceleration(m_gravity);
  }
}
