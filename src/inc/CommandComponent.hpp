#pragma once

#include "Component.hpp"
#include "MotionPhysicsComponent.hpp"

class Command {
  //! Destructor
 public:
  virtual ~Command() noexcept {}

  virtual void execute() = 0;
};

class JumpCommand : public Command {
 public:
  JumpCommand(MotionPhysicsComponent *motion_component)
      : m_motion_component(motion_component) {}
  virtual void execute() {
    m_motion_component->addVelocity(Vector2D<float>(0, -100));  // Temporary
  }

 private:
  MotionPhysicsComponent *m_motion_component;
};

class CommandComponent : public Component {
 public:
  //! Default constructor
  CommandComponent();

  //! Copy constructor
  CommandComponent(const CommandComponent &other) = delete;

  //! Move constructor
  CommandComponent(CommandComponent &&other) noexcept = delete;

  //! Destructor
  virtual ~CommandComponent() noexcept;

  //! Copy assignment operator
  CommandComponent &operator=(const CommandComponent &other) = delete;

  //! Move assignment operator
  CommandComponent &operator=(CommandComponent &&other) noexcept = delete;

  void provide(MotionPhysicsComponent *motion_physics);
  void jump();

 protected:
 private:
  JumpCommand *m_jump_command;
  inline void deleteCommand(Command *command);
};
