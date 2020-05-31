#include "../inc/TransformComponent.hpp"

TransformComponent::TransformComponent()
    : m_position(0, 0),
      m_scale(1, 1),
      m_rotation(0),
      m_transform(nullptr),
      m_modified(true) {}

TransformComponent::TransformComponent(float x, float y)
    : TransformComponent() {
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y)
    : TransformComponent() {
  scale(Vector2D<float>(scale_x, scale_y));
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y, float rotation)
    : TransformComponent() {
  rotate(rotation);
  scale(Vector2D<float>(scale_x, scale_y));
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(const TransformComponent& other)
    : TransformComponent() {
  rotate(other.rotation());
  scale(Vector2D<float>(other.scaleX(), other.scaleY()));
  translate(Vector2D<float>(other.x(), other.y()));
}

TransformComponent::TransformComponent(const luabridge::LuaRef& object)
    : m_position(0, 0), m_scale(0, 0), m_rotation(0) {
  loadFromLua(object);
}

TransformComponent::~TransformComponent() noexcept {
  if (m_transform != nullptr) delete m_transform;
}

float TransformComponent::x() const { return m_position.getX(); }

float TransformComponent::y() const { return m_position.getY(); }

float TransformComponent::scaleX() const { return m_scale.getX(); }

float TransformComponent::scaleY() const { return m_scale.getY(); }

Vector2D<float> TransformComponent::position() const {
  return Vector2D<float>(m_position);
}

Vector2D<float> TransformComponent::scale() const {
  return Vector2D<float>(m_scale);
}

float TransformComponent::rotation() const { return m_rotation; }

Vector2D<float> TransformComponent::origin() const {
  return Vector2D<float>(m_origin);
}

void TransformComponent::setX(float x) {
  m_position.setX(x);
  m_modified = true;
}

void TransformComponent::setY(float y) {
  m_position.setY(y);
  m_modified = true;
}

void TransformComponent::setPosition(const Vector2D<float>& position) {
  m_position.set(position);
  m_modified = true;
}

void TransformComponent::setScaleX(float scale_x) {
  m_scale.setX(scale_x);
  m_modified = true;
}

void TransformComponent::setScaleY(float scale_y) {
  m_scale.setY(scale_y);
  m_modified = true;
}

void TransformComponent::setScale(const Vector2D<float>& scale) {
  m_scale.set(scale);
  m_modified = true;
}

void TransformComponent::setRotation(float rotation) {
  while (rotation < 0) {
    rotation += 2 * M_PI;
  }
  while (rotation > 2 * M_PI) {
    rotation -= 2 * M_PI;
  }
  m_rotation = rotation;
  m_modified = true;
}

void TransformComponent::setOriginX(float origin_x) {
  m_origin.setX(origin_x);
  m_modified = true;
}

void TransformComponent::setOriginY(float origin_y) {
  m_origin.setX(origin_y);
  m_modified = true;
}

void TransformComponent::setOrigin(const Vector2D<float>& origin) {
  m_origin.set(origin);
  m_modified = true;
}

void TransformComponent::loadFromLua(const luabridge::LuaRef& object) {
  m_position.set(object["x"].cast<float>(), object["y"].cast<float>());
  m_scale.set(object["scale_x"].cast<float>(), object["scale_y"].cast<float>());
  m_rotation = object["rotation"].cast<float>();
  m_modified = true;
}

void TransformComponent::translate(const Vector2D<float>& move) {
  m_position += move;
  m_modified = true;
}

void TransformComponent::translate(float z) {
  m_position += z;
  m_modified = true;
}

void TransformComponent::scale(const Vector2D<float>& scale) {
  m_scale *= scale;
  m_modified = true;
}

void TransformComponent::scale(float z) {
  m_scale *= z;
  m_modified = true;
}

void TransformComponent::rotate(float angle) {
  this->setRotation(m_rotation + angle);
  m_modified = true;
}

sf::Transform* TransformComponent::transform() {
  if (m_modified) {
    if (m_transform != nullptr) delete m_transform;
    m_transform = new sf::Transform();
    if (m_rotation != 0) {
      m_transform->translate(-m_origin.getX(), -m_origin.getY());
      m_transform->rotate(rotation() / M_PI * 180);
      m_transform->translate(m_origin.getX(), m_origin.getY());
    }
    m_transform->scale(scaleX(), scaleY());
    m_transform->translate(x(), y());
    m_modified = false;
  }
  return m_transform;
}

std::ostream& operator<<(std::ostream& stream,
                         const TransformComponent& component) {
  stream << "TransformComponent - x/y/scx/scy/rot : " << component.x() << "/"
         << component.y() << "/" << component.scaleX() << "/"
         << component.scaleY() << "/" << component.rotation();
  return stream;
}
