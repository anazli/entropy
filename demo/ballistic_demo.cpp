#include "ballistic_demo.hpp"

#include <SFML/Graphics.hpp>

const float SCALE = 10.f;  // 1 meter = 10 pixels

int main() {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1200, 800)),
                          "Entropy Engine Demo");
  auto frame_limit = 60;
  window.setFramerateLimit(frame_limit);
  const float dt = 1.f / static_cast<float>(frame_limit);
  auto spaw_position = Vec3f(0.f, window.getSize().y / (2.f * SCALE), 0.f);
  BallisticDemo demo;

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto key_pressed =
                     event->getIf<sf::Event::KeyPressed>()) {
        if (key_pressed->code == sf::Keyboard::Key::Num1) {
          demo.fire(BallisticDemo::PISTOL, spaw_position);
        } else if (key_pressed->code == sf::Keyboard::Key::Num2) {
          demo.fire(BallisticDemo::ARTILLERY, spaw_position);
        } else if (key_pressed->code == sf::Keyboard::Key::Num3) {
          demo.fire(BallisticDemo::FIREBALL, spaw_position);
        } else if (key_pressed->code == sf::Keyboard::Key::Num4) {
          demo.fire(BallisticDemo::LASER, spaw_position);
        }
      }
    }

    demo.update(dt);

    window.clear(sf::Color(20, 20, 25));

    float x = demo.getProjectile().GetPosition().x * SCALE;
    float y = static_cast<float>(window.getSize().y) -
              (demo.getProjectile().GetPosition().y * SCALE);

    sf::CircleShape shape(8.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition({x, y});
    window.draw(shape);
    window.display();
  }

  return 0;
}