#pragma once

#include "engine/particle.hpp"

class BallisticDemo {
 public:
  enum ProjectileType { PISTOL, ARTILLERY, FIREBALL, LASER, CUSTOM };

  const entropy::Particle& getProjectile() const { return m_projectile; }
  entropy::Particle& getProjectile() { return m_projectile; }

  void launchProjectile(ProjectileType type, const Vec3f& spawn_position) {
    float mass;
    Vec3f velocity;
    Vec3f acceleration;
    Vec3f force;
    float damping;

    switch (type) {
      case PISTOL:
        mass = 2.0f;
        velocity = Vec3f(45.f, 0.f, 0.f);
        acceleration = Vec3f(0.f, -1.f, 0.f);
        damping = 0.99f;
        break;
      case ARTILLERY:
        mass = 200.f;
        velocity = Vec3f(40.f, 30.f, 0.f);
        acceleration = Vec3f(0.f, -20.f, 0.f);
        damping = 0.99f;
        break;
      case FIREBALL:
        mass = 1.f;
        velocity = Vec3f(20.f, 0.f, 0.f);
        acceleration = Vec3f(0.f, 0.8f, 0.f);  // Floats up
        damping = 0.9f;
        break;
      case LASER:
        mass = 0.1f;
        velocity = Vec3f(100.f, 0.f, 0.f);
        acceleration = Vec3f(0.f, 0.f, 0.0f);  // No gravity
        damping = 0.99f;
        break;
      case CUSTOM:
        mass = 20.f;
        velocity = Vec3f(0.f, 0.f, 0.f);
        acceleration = Vec3f(0.f, 0.f, 0.f);
        force = Vec3f(4000.f, 4000.f, 0.f);
        damping = 0.99f;
        break;
    }
    m_projectile = entropy::Particle(1. / mass, spawn_position, velocity,
                                     acceleration, damping);
    m_projectile.AddForceAccumulator(force);
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
    m_projectile.ClearForceAccumulator();

    if (m_projectile.GetPosition().y <= 0.f) {
      m_is_active = false;
    }
  }

 private:
  entropy::Particle m_projectile;
  bool m_is_active = false;
};
