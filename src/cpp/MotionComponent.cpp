#include "../inc/MotionComponent.hpp"

MotionComponent::MotionComponent() : m_velocity(0, 0), m_acceleration(0, 0) {}

MotionComponent::MotionComponent(const Vector2D<float> &velocity)
    : m_velocity(velocity), m_acceleration(0, 0) {}

MotionComponent::MotionComponent(const Vector2D<float> &velocity,
                                 const Vector2D<float> &acceleration)
    : m_velocity(velocity), m_acceleration(acceleration) {}

MotionComponent::MotionComponent(MotionComponent &&other) noexcept
    : m_velocity(other.m_velocity), m_acceleration(other.m_acceleration) {}

MotionComponent::MotionComponent(luabridge::LuaRef &object) {
  loadFromLua(object);
}

MotionComponent &MotionComponent::operator=(MotionComponent &&other) noexcept {
  m_velocity.set(other.m_velocity);
  m_acceleration.set(other.m_acceleration);
  return *this;
}

void MotionComponent::loadFromLua(luabridge::LuaRef &object) {
  m_velocity.set(object["dx"].cast<float>(), object["dy"].cast<float>());
  m_acceleration.set(object["ddx"].cast<float>(), object["ddy"].cast<float>());
}

Vector2D<float> MotionComponent::getVelocity() const {
  return Vector2D<float>(m_velocity);
}

Vector2D<float> MotionComponent::getAcceleration() const {
  return Vector2D<float>(m_acceleration);
}

void MotionComponent::setAcceleration(const Vector2D<float> ddxy) {
  m_acceleration.set(ddxy);
}

void MotionComponent::setVelocity(float ratio) {
  m_velocity += m_acceleration * ratio;
}

void MotionComponent::setVelocity(const Vector2D<float> dxy) {
  m_velocity.set(dxy);
}

void MotionComponent::addVelocity(const Vector2D<float> ddxy) {
  m_velocity += ddxy;
}

void MotionComponent::addAcceleration(const Vector2D<float> ddxy) {
  m_acceleration += ddxy;
}

void MotionComponent::accelerate(const float ddx) {
  assert(m_acceleration.length() > 0);
  float x = m_acceleration.x;
  float y = m_acceleration.y;
  float x_comp = ddx * x / (x + y);
  m_acceleration += Vector2D<float>(x_comp, ddx - x_comp);
}

void MotionComponent::decelerate(const float ddx) { accelerate(-ddx); }

void MotionComponent::halt() {
  setVelocity(Vector2D<float>(0, 0));
  setVelocity(Vector2D<float>(0, 0));
}
