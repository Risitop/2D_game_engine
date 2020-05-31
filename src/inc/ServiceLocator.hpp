#pragma once

#include "Application.hpp"
#include "EventHandler.hpp"
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

  static void provide(EventHandler* event_service) { m_event = event_service; }
  static EventHandler* Event() { return m_event; }

  static void provide(Application* app_service) { m_application = app_service; }
  static Application* App() { return m_application; }

 private:
  static FileService* m_file;
  static TextureHandler* m_texture;
  static EventHandler* m_event;
  static Application* m_application;
};
