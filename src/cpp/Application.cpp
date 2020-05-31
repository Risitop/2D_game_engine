#include "../inc/Application.hpp"

Application::Application() {}

Application::~Application() noexcept { m_window.close(); }

void Application::initialize(int width, int height, std::string title) {
  m_window.create(sf::VideoMode(width, height), title, sf::Style::None);
  m_window.setFramerateLimit(60);
}

void Application::update() {
  m_window.clear(sf::Color::Black);
  for (RenderRequest& request : m_requests) {
    m_window.draw(request.target, request.states);
  }
  m_window.display();
  m_requests.clear();
}
