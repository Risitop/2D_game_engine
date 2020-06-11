#pragma once

#include "CommandComponent.hpp"
#include "System.hpp"

class CommandSystemEntity : public SystemEntity {
  friend class CommandSystem;

 public:
  //! Default constructor
  CommandSystemEntity();

  //! Copy constructor
  CommandSystemEntity(const CommandSystemEntity &other);

  //! Move constructor
  CommandSystemEntity(CommandSystemEntity &&other) noexcept;

  //! Destructor
  virtual ~CommandSystemEntity() noexcept;

  //! Copy assignment operator
  CommandSystemEntity &operator=(const CommandSystemEntity &other);

  //! Move assignment operator
  CommandSystemEntity &operator=(CommandSystemEntity &&other) noexcept;

 protected:
 private:
  CommandComponent *m_command;
};

class CommandSystem : public System {
 public:
  //! Default constructor
  CommandSystem();

  //! Copy constructor
  CommandSystem(const CommandSystem &other);

  //! Move constructor
  CommandSystem(CommandSystem &&other) noexcept;

  //! Destructor
  virtual ~CommandSystem() noexcept;

  //! Copy assignment operator
  CommandSystem &operator=(const CommandSystem &other);

  //! Move assignment operator
  CommandSystem &operator=(CommandSystem &&other) noexcept;

  void update(sf::Time dt) {
    for (CommandSystemEntity *entity : m_entities) {
      entity->m_command->execute();
      entity->m_command->clear();
    }
  }

 protected:
 private:
  std::vector<CommandSystemEntity *> m_entities;
};
