#pragma once

#include <SFML/Graphics/Transform.hpp>

#include "Component.hpp"
#include "Geometry.hpp"
#include "Vector2D.hpp"

#define CT_TRANSFORM 2

class TransformComponent : public Component {
 public:
  static const ComponentType ID = CT_TRANSFORM;
  //! Default constructor
  TransformComponent();
  TransformComponent(float x, float y);
  TransformComponent(float x, float y, float scale_x, float scale_y);
  TransformComponent(float x, float y, float scale_x, float scale_y,
                     float rotation);
  TransformComponent(const luabridge::LuaRef &object);

  //! Copy constructor
  TransformComponent(const TransformComponent &other);

  //! Destructor
  virtual ~TransformComponent() noexcept;

  // Getters
  float x() const;
  float y() const;
  float scaleX() const;
  float scaleY() const;
  Vector2D<float> position() const;
  Vector2D<float> scale() const;
  float rotation() const;
  Vector2D<float> origin() const;

  // Setters
  void setX(float x);
  void setY(float y);
  void setPosition(const Vector2D<float> &position);
  void setScaleX(float scale_x);
  void setScaleY(float scale_y);
  void setScale(const Vector2D<float> &scale);
  void setRotation(float rotation);
  void setOriginX(float origin_x);
  void setOriginY(float origin_y);
  void setOrigin(const Vector2D<float> &origin);
  void loadFromLua(const luabridge::LuaRef &object);

  // Transformers
  void translate(const Vector2D<float> &move);
  void translate(float z);
  void scale(const Vector2D<float> &scale);
  void scale(float z);
  void rotate(float angle);

  sf::Transform *transform();

 protected:
 private:
  Vector2D<float> m_position;
  Vector2D<float> m_scale;
  Vector2D<float> m_origin;
  float m_rotation;  // In radians !
  sf::Transform *m_transform;
  bool m_modified;
};

std::ostream &operator<<(std::ostream &stream,
                         const TransformComponent &component);
