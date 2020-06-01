#include "../inc/CommandComponent.hpp"

CommandComponent::CommandComponent() : m_jump_command(nullptr) {}

CommandComponent::~CommandComponent() noexcept {
  deleteCommand(m_jump_command);
}

void CommandComponent::provide(MotionPhysicsComponent *motion_physics) {
  m_jump_command = new JumpCommand(motion_physics);
}

void CommandComponent::jump() {
  assert(m_jump_command != nullptr);
  m_jump_command->execute();
}

inline void CommandComponent::deleteCommand(Command *command) {
  if (command != nullptr) delete command;
}
