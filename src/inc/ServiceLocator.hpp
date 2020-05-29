#pragma once

#include "FileManager.hpp"
#include "TextureHandler.hpp"

class ServiceLocator {
 public:
  static void provide(FileService* file_service) { m_file = file_service; }
  static FileService* File() { return m_file; }

  static void provide(TextureHandler* texture_service) {
    m_texture = texture_service;
  }
  static TextureHandler* Texture() { return m_texture; }

 private:
  static FileService* m_file;
  static TextureHandler* m_texture;
};
