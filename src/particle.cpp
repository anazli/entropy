#include "engine/particle.hpp"

#include <cassert>

const float eps = 1.E-3;

namespace entropy {
Particle::Particle(float inverse_mass, const Vec3f& position,
                   const Vec3f& velocity, const Vec3f& acceleration,
                   float damping)
    : m_inverse_mass(inverse_mass),
      m_position(position),
      m_velocity(velocity),
      m_acceleration(acceleration),
      m_damping(damping) {}

Vec3f Particle::GetPosition() const { return m_position; }

Vec3f Particle::GetVelocity() const { return m_velocity; }

Vec3f Particle::GetAcceleration() const { return m_acceleration; }

float Particle::GetMass() const { return 1. / m_inverse_mass; }

void Particle::ApplyForce(const Vec3f& force) { m_force = force; }

void Particle::AddForceAccumulator(const Vec3f& force) {
  m_force = m_force + force;
}

void Particle::ClearForceAccumulator() { m_force = Vec3f(); }

void Particle::Integrate(float dt) {
  assert(dt > 0.f);

  if (m_inverse_mass <= 0.f) {
    return;
  }

  m_acceleration = m_acceleration + (m_force * m_inverse_mass);
  m_velocity = m_velocity + m_acceleration * dt;
  m_velocity = m_velocity * std::pow(m_damping, dt);
  m_position = m_position + m_velocity * dt;
}

}  // namespace entropy
