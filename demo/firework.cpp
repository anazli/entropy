#include "firework.hpp"

#include <SFML/Graphics.hpp>

const float SCALE = 10.f;  // 1 meter = 10 pixels

int main() {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1200, 800)),
                          "Firework Demo");
  auto frame_limit = 60;
  window.setFramerateLimit(frame_limit);
  const float dt = 1.f / static_cast<float>(frame_limit);
  auto spawn_position = Vec3f(window.getSize().x / (2.f * SCALE), 12.f, 0.f);
  FireworkDemo demo;

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto key_pressed =
                     event->getIf<sf::Event::KeyPressed>()) {
        if (key_pressed->code == sf::Keyboard::Key::Num1) {
          demo.launchRocket(spawn_position);
        }
      }
    }

    demo.update(dt);

    window.clear(sf::Color(20, 20, 25));

    sf::CircleShape rocket(4.0f);
    rocket.setFillColor(sf::Color::Red);

    sf::CircleShape child(2.0f);

    for (const auto& firework : demo.getFireworks()) {
      float x = firework.particle.Position().x * SCALE;
      float y = static_cast<float>(window.getSize().y) -
                (firework.particle.Position().y * SCALE);

      sf::Vector2f pos(x, y);

      if (firework.is_parent) {
        rocket.setPosition(pos);
        window.draw(rocket);
      } else {
        float life_ratio = std::clamp(firework.age / 1.5f, 0.f, 1.f);
        unsigned char alpha = static_cast<unsigned char>(255.f * life_ratio);

        child.setFillColor(sf::Color(255, 255, 50, alpha));
        child.setPosition(pos);
        window.draw(child);
      }
    }

    window.display();
  }

  return 0;
}