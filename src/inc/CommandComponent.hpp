#pragma once

#include "Component.hpp"
#include "ComponentHandler.hpp"
#include "MotionComponent.hpp"

class Command {
 public:
  //! Default constructor
  Command(Component *target) : m_target(target) {}

  //! Copy constructor
  Command(const Command &other) {}

  //! Move constructor
  Command(Command &&other) noexcept = delete;

  //! Destructor
  virtual ~Command() noexcept {}

  //! Copy assignment operator
  Command &operator=(const Command &other) = delete; 

  //! Move assignment operator
  Command &operator=(Command &&other) noexcept = delete;

  virtual void execute() = 0;

 protected:
  Component *m_target;

 private:
};

class JumpCommand : public Command {
 public:
  //! Default constructor
  JumpCommand(MotionComponent *target) : Command(target) {}

  //! Copy constructor
  JumpCommand(const JumpCommand &other) : Command(other.m_target) {}

  //! Move constructor
  JumpCommand(JumpCommand &&other) noexcept = delete;

  //! Destructor
  virtual ~JumpCommand() noexcept {}

  //! Copy assignment operator
  JumpCommand &operator=(const JumpCommand &other) = delete; 

  //! Move assignment operator
  JumpCommand &operator=(JumpCommand &&other) noexcept = delete;

  virtual void execute() {
    MotionComponent *target = static_cast<MotionComponent *>(m_target);
    target->addVelocity(Vector2D<float>(0, -50));
  }

 protected:
 private:
};

class CommandComponent : public Component {
 public:
  //! Default constructor
  CommandComponent();

  //! Copy constructor
  CommandComponent(const CommandComponent &other) = delete;

  //! Move constructor
  CommandComponent(CommandComponent &&other) noexcept;

  //! Destructor
  virtual ~CommandComponent() noexcept;

  //! Copy assignment operator
  CommandComponent &operator=(const CommandComponent &other);

  //! Move assignment operator
  CommandComponent &operator=(CommandComponent &&other) noexcept;

  void execute() {
    for (Command* command : m_commands) {
      command->execute();
    }
  }

  void addCommand(Command *command) { m_commands.push_back(command); }
  void clear() {
    for (Command *command : m_commands) {
      delete command;
    }
    m_commands.clear();
  }

 protected:
 private:
  std::vector<Command *> m_commands;
};

