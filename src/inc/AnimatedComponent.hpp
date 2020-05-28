#pragma once

#include <assert.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <iterator>
#include <string>
#include <vector>

#define CT_ANIMATED 0

#include "Component.hpp"

typedef unsigned int uint;

class AnimatedComponent : public Component {
 public:
  static const ComponentType ID = CT_ANIMATED;
  //! Default constructor
  AnimatedComponent();

  //! Copy constructor
  AnimatedComponent(const AnimatedComponent& other);

  //! Lua constructor
  AnimatedComponent(luabridge::LuaRef& object);

  //! Destructor
  virtual ~AnimatedComponent() noexcept;

  // Getters
  uint size() const;
  sf::IntRect frame() const;
  bool looping() const;
  bool playing() const;

  // Setters
  void addFrame(const sf::IntRect frame);
  void setFrameTime(sf::Time frame_time);
  void setLooping(bool b);

  void loadFromLua(luabridge::LuaRef& object);

  // Actors
  void stop();
  void play();
  void pause();
  void update(sf::Time delta);

 protected:
 private:
  uint m_active_frame;
  sf::Time m_frame_time;
  sf::Time m_current_time;
  bool m_paused;
  bool m_looped;
  std::vector<sf::IntRect> m_frames;

  sf::IntRect getFrameByIndex(uint i) const;
};

std::ostream& operator<<(std::ostream& stream,
                         const AnimatedComponent& component);
