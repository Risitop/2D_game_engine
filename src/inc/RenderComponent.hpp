#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Component.hpp"
#include "ServiceLocator.hpp"

#define CT_DRAWABLE 1;

/*
 * A drawable component contains information about texturing a sprite
 */
class RenderComponent : public Component {
 public:
  static const ComponentType ID = CT_DRAWABLE;
  //! Default constructor
  RenderComponent();
  RenderComponent(sf::Texture* texture);
  RenderComponent(sf::Texture* texture, sf::IntRect& frame);
  RenderComponent(luabridge::LuaRef& object);

  //! Copy constructor
  RenderComponent(const RenderComponent& other);

  //! Destructor
  virtual ~RenderComponent() noexcept;

  // Getters
  int zIndex() const;
  sf::Texture* getTexture() const;
  sf::IntRect getFrame() const;
  sf::Sprite getSprite() const;

  // Setters
  void setZIndex(int index);
  void setTexture(sf::Texture* texture);
  void setFrame(const sf::IntRect& rect);
  void loadFromLua(luabridge::LuaRef& object);

 protected:
 private:
  int m_zIndex;
  sf::Texture* m_texture;  //! A pointer towards the current texture
  sf::IntRect m_frame;
  sf::Sprite m_sprite;
};

std::ostream& operator<<(std::ostream& stream, RenderComponent& component);
