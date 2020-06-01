#pragma once

#include "Component.hpp"
#include "Vector2D.hpp"

#define CT_MOTION 3

class MotionComponent : public Component {
 public:
  static const ComponentType ID = CT_MOTION;
  //! Default constructor
  MotionComponent();
  MotionComponent(const Vector2D<float> &velocity);
  MotionComponent(const Vector2D<float> &velocity,
                  const Vector2D<float> &acceleration);
  MotionComponent(luabridge::LuaRef &object);

  //! Copy constructor
  MotionComponent(const MotionComponent &other) = delete;

  //! Move constructor
  MotionComponent(MotionComponent &&other) noexcept;

  //! Destructor
  virtual ~MotionComponent() noexcept {}

  //! Copy assignment operator
  MotionComponent &operator=(const MotionComponent &other) = delete;

  //! Move assignment operator
  MotionComponent &operator=(MotionComponent &&other) noexcept;

  void loadFromLua(luabridge::LuaRef &object);

  Vector2D<float> getVelocity() const;
  Vector2D<float> getAcceleration() const;

  void setAcceleration(const Vector2D<float> ddxy);
  void setVelocity(float ratio);  // Ratio = dt/dt(true)
  void setVelocity(const Vector2D<float> dxy);

  void addVelocity(const Vector2D<float> ddxy);
  void addAcceleration(const Vector2D<float> ddxy);
  void accelerate(const float ddx);
  void decelerate(const float ddx);
  void halt();

 protected:
 private:
  Vector2D<float> m_velocity;
  Vector2D<float> m_acceleration;
};
