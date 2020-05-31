#include "../inc/RenderComponent.hpp"

RenderComponent::RenderComponent() {}

RenderComponent::RenderComponent(sf::Texture* texture) : m_texture(texture) {}

RenderComponent::RenderComponent(sf::Texture* texture, sf::IntRect& frame)
    : m_texture(texture) {
  this->setFrame(frame);
}

RenderComponent::RenderComponent(luabridge::LuaRef& object)
    : m_zIndex(0), m_texture(NULL), m_frame(), m_sprite() {
  loadFromLua(object);
}

RenderComponent::RenderComponent(const RenderComponent& other)
    : m_texture(other.m_texture) {
  this->setFrame(other.getFrame());
}

// We do not destroy texture as several RenderComponents may be using it.
RenderComponent::~RenderComponent() noexcept {}

int RenderComponent::zIndex() const { return m_zIndex; }

// The texture is not encapsulated, as accessed by several RenderComponents.
sf::Texture* RenderComponent::getTexture() const { return m_texture; }

sf::IntRect RenderComponent::getFrame() const { return sf::IntRect(m_frame); }

sf::Sprite RenderComponent::getSprite() const { return sf::Sprite(m_sprite); }

void RenderComponent::setZIndex(int index) { m_zIndex = index; }

void RenderComponent::setTexture(sf::Texture* texture) {
  m_texture = texture;
  m_sprite.setTexture(*texture);
}

void RenderComponent::setFrame(const sf::IntRect& rect) {
  m_frame = sf::IntRect(rect);
  m_sprite.setTextureRect(m_frame);
}

void RenderComponent::loadFromLua(luabridge::LuaRef& object) {
  m_zIndex = object["zIndex"].cast<int>();

  int x_rect = object["frame"]["x"].cast<int>();
  int y_rect = object["frame"]["y"].cast<int>();
  int w_rect = object["frame"]["w"].cast<int>();
  int h_rect = object["frame"]["h"].cast<int>();
  m_frame = sf::IntRect(x_rect, y_rect, w_rect, h_rect);

  setTexture(
      ServiceLocator::Texture()->getTexture(object["atlas_id"].cast<int>()));
}

std::ostream& operator<<(std::ostream& stream, RenderComponent& component) {
  sf::IntRect frame = component.getFrame();
  int x = frame.left;
  int y = frame.top;
  int w = frame.width;
  int h = frame.height;
  stream << "RenderComponent - zIndex/frame(x,y,w,h) : " << component.zIndex()
         << "/" << x << "," << y << "," << w << "," << h;
  return stream;
}
