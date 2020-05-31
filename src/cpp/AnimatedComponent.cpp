#include "../inc/AnimatedComponent.hpp"

AnimatedComponent::AnimatedComponent()
    : m_active_frame(0),
      m_frame_time(sf::Time::Zero),
      m_current_time(sf::Time::Zero),
      m_paused(false),
      m_looped(true) {}

AnimatedComponent::AnimatedComponent(const AnimatedComponent& other)
    : m_active_frame(other.m_active_frame),
      m_frame_time(other.m_frame_time),
      m_current_time(other.m_current_time),
      m_paused(other.m_paused),
      m_looped(other.m_looped) {
  for (sf::IntRect frame : other.m_frames) {
    addFrame(frame);
  }
}

AnimatedComponent::AnimatedComponent(luabridge::LuaRef& object)
    : m_active_frame(0), m_current_time(sf::Time::Zero), m_paused(false) {
  loadFromLua(object);
}

AnimatedComponent::~AnimatedComponent() noexcept {}

uint AnimatedComponent::size() const { return m_frames.size(); }

sf::IntRect AnimatedComponent::frame() const {
  assert(m_active_frame >= 0 && m_active_frame < size());
  return sf::IntRect(m_frames[m_active_frame]);
}

bool AnimatedComponent::looping() const { return m_looped; }

bool AnimatedComponent::playing() const { return !m_paused; }

void AnimatedComponent::addFrame(const sf::IntRect frame) {
  m_frames.push_back(frame);
}

void AnimatedComponent::setFrameTime(sf::Time frame_time) {
  m_frame_time = frame_time;
}

void AnimatedComponent::setLooping(bool b) { m_looped = b; }

void AnimatedComponent::loadFromLua(luabridge::LuaRef& object) {
  m_frame_time = sf::milliseconds(object["frame_time"].cast<int>());
  m_looped = object["looped"].cast<bool>();
  int n_frames = object["n_frames"].cast<int>();
  for (int i = 0; i < n_frames; i++) {
    luabridge::LuaRef frame =
        object["frames"]["frame_" + std::to_string(i + 1)];
    int x = frame["x"].cast<int>();
    int y = frame["y"].cast<int>();
    int w = frame["w"].cast<int>();
    int h = frame["h"].cast<int>();
    addFrame(sf::IntRect(x, y, w, h));
  }
}

void AnimatedComponent::stop() {
  pause();
  m_active_frame = 0;
  m_current_time = sf::Time::Zero;
}

void AnimatedComponent::play() { m_paused = false; }

void AnimatedComponent::pause() { m_paused = true; }

void AnimatedComponent::update(sf::Time delta) {
  if (m_paused) return;

  m_current_time += delta;
  if (m_current_time < m_frame_time) return;

  m_current_time = sf::microseconds(m_current_time.asMicroseconds() %
                                    m_frame_time.asMicroseconds());
  m_active_frame++;

  if (m_active_frame == size() && !looping()) {
    pause();
    return;
  }

  if (m_active_frame == size()) {
    m_active_frame = 0;
  }
}

std::ostream& operator<<(std::ostream& stream,
                         const AnimatedComponent& component) {
  sf::IntRect frame = component.frame();
  stream << "AnimatedComponent - s/f/l/p : " << component.size() << "/"
         << frame.left << "," << frame.top << "," << frame.width << ","
         << frame.height << "/" << component.looping() << "/"
         << component.playing();
  return stream;
}
