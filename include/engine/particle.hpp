#pragma once

#include <vec3.h>

namespace entropy {
class Particle {
 public:
  Particle(float inverse_mass, const Vec3f& position, const Vec3f& velocity,
           const Vec3f& acceleration, float damping, const Vec3f& force);
  Vec3f GetPosition() const;
  Vec3f GetVelocity() const;
  Vec3f GetAcceleration() const;

  void Integrate(float duration);

 private:
  Vec3f m_position;
  Vec3f m_velocity;
  Vec3f m_acceleration;
  Vec3f m_force;
  float m_inverse_mass{0.f};
  float m_damping{0.99};
};
}  // namespace entropy