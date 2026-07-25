#pragma once

#include <random>
#include <vector>

#include "engine/particle.hpp"

struct Firework {
  entropy::Particle particle;
  float age;
  bool is_parent;
};

class FireworkDemo {
 public:
  const std::vector<Firework>& getFireworks() const { return m_fireworks; }
  std::vector<Firework>& getFireworks() { return m_fireworks; }

  void launchRocket(const Vec3f& position) {
    Firework rocket;
    Vec3f velocity(0.f, 30.f, 0.f);
    Vec3f acceleration(0.f, -9.81f, 0.f);
    float damping = 0.99;
    float inverse_mass = 1.f;
    float age = 1.f;
    rocket.particle = entropy::Particle(inverse_mass, position, velocity,
                                        acceleration, damping);
    rocket.age = age;
    rocket.is_parent = true;
    m_fireworks.push_back(rocket);
  }

  void explode(const Vec3f& position) {
    if (m_fireworks.size() > 500) {
      return;
    }
    std::uniform_real_distribution<float> rnd(0.f, 1.f);
    for (int i = 0; i < 20; ++i) {
      float angle = rnd(m_gen) * 2.f * static_cast<float>(acos(-1.));
      float speed = 10.f + (rnd(m_gen)) * 20.f;

      Firework child;
      Vec3f velocity(std::cos(angle) * speed, std::sin(angle) * speed, 0.f);
      Vec3f acceleration(0.f, -9.81f, 0.f);
      float damping = 0.99;
      float inverse_mass = 2.f;
      float age = 1.f + 0.5f * rnd(m_gen);
      child.particle = entropy::Particle(inverse_mass, position, velocity,
                                         acceleration, damping);
      child.age = age;
      if (rnd(m_gen) < 0.1f) {
        child.is_parent = false;
      } else {
        child.is_parent = true;
      }
      m_fireworks.push_back(child);
    }
  }

  void update(float dt) {
    for (int i = m_fireworks.size() - 1; i >= 0; --i) {
      auto& firework = m_fireworks[i];
      firework.particle.Integrate(dt);
      firework.age -= dt;
      if (firework.age <= 0.f) {
        if (firework.is_parent) {
          explode(firework.particle.Position());
        }
        m_fireworks.erase(m_fireworks.begin() + i);
      }
    }
  }

 private:
  std::vector<Firework> m_fireworks;
  std::mt19937 m_gen = std::mt19937(139575u);
};