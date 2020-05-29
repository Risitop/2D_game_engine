#include "../inc/TextureHandler.hpp"

TextureHandler::TextureHandler() {}

TextureHandler::~TextureHandler() { clear(); }

void TextureHandler::addAtlas(const std::string& atlas_path, AtlasID atlas_id) {
  while (m_atlases.size() <= atlas_id) {
    sf::Texture* place_holder = new sf::Texture();
    m_atlases.push_back(place_holder);
  }
  sf::Texture* texture = m_atlases[atlas_id];
  if (!texture->loadFromFile(atlas_path)) {
    throw "Unknown atlas path.";
  }
  std::cout << "Texture " << atlas_id << " successfully loaded."
            << "\n";
}

void TextureHandler::clear() {
  for (sf::Texture* texture : m_atlases) {
    delete texture;
  }
  m_atlases.clear();
}

sf::Texture* TextureHandler::getTexture(AtlasID atlas_id) {
  assert(atlas_id < m_atlases.size());
  return m_atlases[atlas_id];
}
