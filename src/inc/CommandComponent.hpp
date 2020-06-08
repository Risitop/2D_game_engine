#pragma once

#include "ComponentHandler.hpp"

class Command {
 public:
  //! Default constructor
  Command() {}

  //! Copy constructor
  Command(const Command &other) {}

  //! Move constructor
  Command(Command &&other) noexcept = delete;

  //! Destructor
  virtual ~Command() noexcept {}

  //! Copy assignment operator
  Command &operator=(const Command &other) {}

  //! Move assignment operator
  Command &operator=(Command &&other) noexcept = delete;

  static void execute(Component *component) {}

 protected:
 private:
};

class JumpCommand : public Command {
 public:
  //! Default constructor
  JumpCommand() {}

  //! Copy constructor
  JumpCommand(const JumpCommand &other) {}

  //! Move constructor
  JumpCommand(JumpCommand &&other) noexcept = delete;

  //! Destructor
  virtual ~JumpCommand() noexcept {}

  //! Copy assignment operator
  JumpCommand &operator=(const JumpCommand &other) {}

  //! Move assignment operator
  JumpCommand &operator=(JumpCommand &&other) noexcept = delete;

  static void execute(MotionComponent *component) {
    component->addVelocity(Vector2D<float>(0, -50));
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
