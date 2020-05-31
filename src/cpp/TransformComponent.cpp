#include "../inc/TransformComponent.hpp"

TransformComponent::TransformComponent()
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {}

TransformComponent::TransformComponent(float x, float y)
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y)
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {
  scale(Vector2D<float>(scale_x, scale_y));
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(float x, float y, float scale_x,
                                       float scale_y, float rotation)
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {
  rotate(rotation);
  scale(Vector2D<float>(scale_x, scale_y));
  translate(Vector2D<float>(x, y));
}

TransformComponent::TransformComponent(const TransformComponent& other)
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {
  rotate(other.rotation());
  scale(Vector2D<float>(other.scaleX(), other.scaleY()));
  translate(Vector2D<float>(other.x(), other.y()));
}

TransformComponent::TransformComponent(const luabridge::LuaRef& object)
    : m_position(0, 0), m_scale(1, 1), m_rotation(0), m_modified(true) {
  loadFromLua(object);
}

TransformComponent::~TransformComponent() noexcept {}

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

//! rect: frame
void TransformComponent::getVertices(const sf::IntRect& rect, sf::Vertex* ret) {
  // Recalculating transform matrix
  if (m_modified) {
    float c = cos(m_rotation);
    float s = sin(m_rotation);
    float sx = m_scale.getX();
    float sy = m_scale.getY();
    m_transform.coords[0] = c * sx;
    m_transform.coords[1] = -s * sx;
    m_transform.coords[2] = s * sy;
    m_transform.coords[3] = c * sy;
    m_modified = false;
  }

  // Centering frame
  Vector2D<float> p00 = Vector2D<float>(-rect.width, -rect.height) * 0.5;
  Vector2D<float> p10 = Vector2D<float>(rect.width, -rect.height) * 0.5;
  Vector2D<float> p11 = Vector2D<float>(rect.width, rect.height) * 0.5;
  Vector2D<float> p01 = Vector2D<float>(-rect.width, rect.height) * 0.5;

  ret[0] = sf::Vertex(m_transform.dot(p00) + m_position);
  ret[1] = sf::Vertex(m_transform.dot(p10) + m_position);
  ret[2] = sf::Vertex(m_transform.dot(p11) + m_position);
  ret[3] = sf::Vertex(m_transform.dot(p01) + m_position);
}

std::ostream& operator<<(std::ostream& stream,
                         const TransformComponent& component) {
  stream << "TransformComponent - x/y/scx/scy/rot : " << component.x() << "/"
         << component.y() << "/" << component.scaleX() << "/"
         << component.scaleY() << "/" << component.rotation();
  return stream;
}
