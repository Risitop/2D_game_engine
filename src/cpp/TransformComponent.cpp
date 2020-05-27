#include "../inc/TransformComponent.hpp"

TransformComponent::TransformComponent()
    : m_position(0, 0), m_scale(0, 0), m_rotation(0) {}

TransformComponent::TransformComponent(float x, float y)
    : m_position(x, y), m_scale(0, 0), m_rotation(0) {}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y)
    : m_position(x, y), m_scale(scale_x, scale_y), m_rotation(0) {}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y, float rotation)
    : m_position(x, y), m_scale(scale_x, scale_y), m_rotation(rotation) {}

TransformComponent::TransformComponent(const TransformComponent& other)
    : m_position(other.x(), other.y()),
      m_scale(other.scaleX(), other.scaleY()),
      m_rotation(other.rotation()) {}

TransformComponent::TransformComponent(luabridge::LuaRef& object)
    : m_position(0, 0), m_scale(0, 0), m_rotation(0) {
  loadFromLua(object);
}

TransformComponent::~TransformComponent() noexcept {}

float TransformComponent::x() const { return m_position.x(); }

float TransformComponent::y() const { return m_position.y(); }

float TransformComponent::scaleX() const { return m_scale.x(); }

float TransformComponent::scaleY() const { return m_scale.y(); }

Vector2D TransformComponent::position() const { return Vector2D(m_position); }

Vector2D TransformComponent::scale() const { return Vector2D(m_scale); }

float TransformComponent::rotation() const { return m_rotation; }

void TransformComponent::setX(float x) { m_position.setX(x); }

void TransformComponent::setY(float y) { m_position.setY(y); }

void TransformComponent::setPosition(Vector2D position) {
  m_position.set(position);
}

void TransformComponent::setScaleX(float scale_x) { m_scale.setX(scale_x); }

void TransformComponent::setScaleY(float scale_y) { m_scale.setY(scale_y); }

void TransformComponent::setScale(Vector2D scale) { m_scale.set(scale); }

void TransformComponent::setRotation(float rotation) {
  while (rotation < 0) {
    rotation += 2 * Geometry::M_PI;
  }
  while (rotation > 2 * Geometry::M_PI) {
    rotation -= 2 * Geometry::M_PI;
  }
  m_rotation = rotation;
}

void TransformComponent::loadFromLua(luabridge::LuaRef& object) {
  m_position.set(object["x"].cast<float>(), object["y"].cast<float>());
  m_scale.set(object["scale_x"].cast<float>(), object["scale_y"].cast<float>());
  m_rotation = object["rotation"].cast<float>();
}

void TransformComponent::translate(Vector2D move) { m_position += move; }

void TransformComponent::scale(Vector2D scale) { m_scale *= scale; }

void TransformComponent::rotate(float angle) {
  this->setRotation(m_rotation + angle);
}

std::ostream& operator<<(std::ostream& stream,
                         const TransformComponent& component) {
  stream << "TransformComponent - x/y/scx/scy/rot : " << component.x() << "/"
         << component.y() << "/" << component.scaleX() << "/"
         << component.scaleY() << "/" << component.rotation();
  return stream;
}
