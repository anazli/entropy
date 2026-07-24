#pragma once

#include <vec3.h>

namespace entropy {
class Particle {
 public:
  Particle() = default;
  Particle(float inverse_mass, const Vec3f& position, const Vec3f& velocity,
           const Vec3f& acceleration, float damping);
  Vec3f Position() const;
  Vec3f Velocity() const;
  Vec3f Acceleration() const;
  float Mass() const;

  void ApplyForce(const Vec3f& force);
  void AddForce(const Vec3f& force);
  void ClearForces();

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