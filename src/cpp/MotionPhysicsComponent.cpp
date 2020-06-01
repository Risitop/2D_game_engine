#include "../inc/MotionPhysicsComponent.hpp"

MotionPhysicsComponent::MotionPhysicsComponent()
    : m_velocity(0, 0), m_acceleration(0, 0) {}

MotionPhysicsComponent::MotionPhysicsComponent(const Vector2D<float> &velocity)
    : m_velocity(velocity), m_acceleration(0, 0) {}

MotionPhysicsComponent::MotionPhysicsComponent(
    const Vector2D<float> &velocity, const Vector2D<float> &acceleration)
    : m_velocity(velocity), m_acceleration(acceleration) {}

MotionPhysicsComponent::MotionPhysicsComponent(
    MotionPhysicsComponent &&other) noexcept
    : m_velocity(other.m_velocity), m_acceleration(other.m_acceleration) {}

MotionPhysicsComponent &MotionPhysicsComponent::operator=(
    MotionPhysicsComponent &&other) noexcept {
  m_velocity.set(other.m_velocity);
  m_acceleration.set(other.m_acceleration);
  return *this;
}

Vector2D<float> MotionPhysicsComponent::getVelocity() const {
  return Vector2D<float>(m_velocity);
}

Vector2D<float> MotionPhysicsComponent::getAcceleration() const {
  return Vector2D<float>(m_acceleration);
}

void MotionPhysicsComponent::setAcceleration(const Vector2D<float> ddxy) {
  m_acceleration.set(ddxy);
}

void MotionPhysicsComponent::setVelocity() { m_velocity += m_acceleration; }

void MotionPhysicsComponent::setVelocity(const Vector2D<float> dxy) {
  m_velocity.set(dxy);
}

void MotionPhysicsComponent::addVelocity(const Vector2D<float> ddxy) {
  m_velocity += ddxy;
}

void MotionPhysicsComponent::addAcceleration(const Vector2D<float> ddxy) {
  m_acceleration += ddxy;
}

void MotionPhysicsComponent::accelerate(const float ddx) {
  assert(m_acceleration.length() > 0);
  float x = m_acceleration.x;
  float y = m_acceleration.y;
  float x_comp = ddx * x / (x + y);
  m_acceleration += Vector2D<float>(x_comp, ddx - x_comp);
}

void MotionPhysicsComponent::decelerate(const float ddx) { accelerate(-ddx); }

void MotionPhysicsComponent::halt() {
  setVelocity(Vector2D<float>(0, 0));
  setVelocity(Vector2D<float>(0, 0));
}
