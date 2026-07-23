#pragma once

#include "engine/particle.hpp"

class BallisticDemo {
 public:
  enum ProjectileType { PISTOL, ARTILLERY, FIREBALL, LASER };

  const entropy::Particle& getProjectile() const { return m_projectile; }

  void launchProjectile(ProjectileType type, const Vec3f& spawn_position) {
    float mass;
    Vec3f velocity;
    Vec3f acceleration;
    float damping;

    switch (type) {
      case PISTOL:
        mass = 2.0f;
        velocity = Vec3f(55.0f, 0.0f, 0.0f);
        acceleration = Vec3f(0.0f, -1.0f, 0.0f);
        damping = 0.99f;
        break;
      case ARTILLERY:
        mass = 200.0f;
        velocity = Vec3f(0.0f, 30.0f, 40.0f);  // 50m/s
        acceleration = Vec3f(0.0f, -20.0f, 0.0f);
        damping = 0.99f;
        break;
      case FIREBALL:
        mass = 1.0f;
        velocity = Vec3f(0.0f, 0.0f, 10.0f);     // 5m/s
        acceleration = Vec3f(0.0f, 0.6f, 0.0f);  // Floats up
        damping = 0.9f;
        break;
      case LASER:
        mass = 0.1f;
        velocity = Vec3f(0.0f, 0.0f, 100.0f);    // 100m/s
        acceleration = Vec3f(0.0f, 0.0f, 0.0f);  // No gravity
        damping = 0.99f;
        break;
    }
    m_projectile = entropy::Particle(1. / mass, spawn_position, velocity,
                                     acceleration, damping, Vec3f());
  }

  void fire(ProjectileType type, const Vec3f& spawn_position) {
    m_is_active = true;
    launchProjectile(type, spawn_position);
  }

  void update(float dt) {
    if (!m_is_active) {
      return;
    }

    m_projectile.Integrate(dt);

    if (m_projectile.GetPosition().y <= 0.f) {
      m_is_active = false;
    }
  }

 private:
  entropy::Particle m_projectile;
  bool m_is_active = false;
};
