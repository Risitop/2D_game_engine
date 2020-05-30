#pragma once

#include <SFML/Graphics.hpp>

class Application {
  friend class EventHandler;

 public:
  //! Default constructor
  Application();

  //! Copy constructor
  Application(const Application &other) = delete;

  //! Move constructor
  Application(Application &&other) noexcept = delete;

  //! Destructor
  virtual ~Application() noexcept;

  //! Copy assignment operator
  Application &operator=(const Application &other) = delete;

  //! Move assignment operator
  Application &operator=(Application &&other) noexcept = delete;

  void initialize(int width, int height, std::string title);
  bool isOpen() { return m_window.isOpen(); }
  bool pollEvent(sf::Event &event) { return m_window.pollEvent(event); }
  void close() { m_window.close(); }
  void update();

 protected:
 private:
  sf::RenderWindow m_window;
};
