#pragma once

#include "Component.hpp"
#include "Vector2D.hpp"

class MotionPhysicsComponent : public Component {
 public:
  //! Default constructor
  MotionPhysicsComponent();
  MotionPhysicsComponent(const Vector2D<float> &velocity);
  MotionPhysicsComponent(const Vector2D<float> &velocity,
                         const Vector2D<float> &acceleration);

  //! Copy constructor
  MotionPhysicsComponent(const MotionPhysicsComponent &other) = delete;

  //! Move constructor
  MotionPhysicsComponent(MotionPhysicsComponent &&other) noexcept;

  //! Destructor
  virtual ~MotionPhysicsComponent() noexcept {}

  //! Copy assignment operator
  MotionPhysicsComponent &operator=(const MotionPhysicsComponent &other) =
      delete;

  //! Move assignment operator
  MotionPhysicsComponent &operator=(MotionPhysicsComponent &&other) noexcept;

  Vector2D<float> getVelocity() const;
  Vector2D<float> getAcceleration() const;

  void setAcceleration(const Vector2D<float> ddxy);
  void setVelocity();
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
