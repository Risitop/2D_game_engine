#pragma once

typedef unsigned int AtlasID;

#include <assert.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <vector>

#include "Lua.hpp"

class TextureHandler {
  friend class GameEngine;

 public:
  //! Default constructor
  TextureHandler();

  //! Copy constructor
  TextureHandler(const TextureHandler &other) = delete;

  //! Move constructor
  TextureHandler(TextureHandler &&other) noexcept = delete;

  //! Destructor
  virtual ~TextureHandler() noexcept;

  //! Copy assignment operator
  TextureHandler &operator=(const TextureHandler &other) = delete;

  //! Move assignment operator
  TextureHandler &operator=(TextureHandler &&other) noexcept = delete;

  //! Render components get their texture using this accessor
  sf::Texture *getTexture(AtlasID atlas_id);

 protected:
  //! For Game Engine only
  void loadAtlases(luabridge::LuaRef &object);
  void clear();

 private:
  void addAtlas(const std::string &atlas_path, AtlasID atlas_id);
  std::vector<sf::Texture *> m_atlases;
};
