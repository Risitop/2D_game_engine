#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct RenderRequest {
  sf::VertexArray target;
  sf::RenderStates states;
};

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

  // Interface for sf::RenderWindow
  void initialize(int width, int height, std::string title);
  bool isOpen() { return m_window.isOpen(); }
  bool pollEvent(sf::Event &event) { return m_window.pollEvent(event); }
  void close() { m_window.close(); }
  void update();
  void draw(const sf::VertexArray &vertex_array,
            const sf::RenderStates &states = sf::RenderStates::Default) {
    RenderRequest request;
    request.target = vertex_array;
    request.states = states;
    m_requests.push_back(request);
  }

 protected:
 private:
  sf::RenderWindow m_window;
  std::vector<RenderRequest> m_requests;
};
