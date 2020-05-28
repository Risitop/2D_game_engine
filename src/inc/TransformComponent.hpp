#pragma once

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
  TransformComponent(luabridge::LuaRef &object);

  //! Copy constructor
  TransformComponent(const TransformComponent &other);

  //! Destructor
  virtual ~TransformComponent() noexcept;

  // Getters
  float x() const;
  float y() const;
  float scaleX() const;
  float scaleY() const;
  Vector2D position() const;
  Vector2D scale() const;
  float rotation() const;

  // Setters
  void setX(float x);
  void setY(float y);
  void setPosition(Vector2D position);
  void setScaleX(float scale_x);
  void setScaleY(float scale_y);
  void setScale(Vector2D scale);
  void setRotation(float rotation);
  void loadFromLua(luabridge::LuaRef &object);

  // Transformers
  void translate(Vector2D move);
  void scale(Vector2D scale);
  void rotate(float angle);

 protected:
 private:
  Vector2D m_position;
  Vector2D m_scale;
  float m_rotation;  // In radians !
};

std::ostream &operator<<(std::ostream &stream,
                         const TransformComponent &component);
