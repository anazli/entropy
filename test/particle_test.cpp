#include "engine/particle.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

class ParticleTest : public testing::Test {
 public:
  Vec3f position;
  Vec3f velocity;
  Vec3f force;
  Vec3f acceleration;
  float damping;
  float inverse_mass;
};

TEST_F(ParticleTest,
       FirstLaw_ParticleKeepsMovingWithConstantSpeedWhenNoForceApplied) {
  position = acceleration = force = Vec3f();
  velocity = Vec3f(10.f, 0.f, 0.f);
  damping = inverse_mass = 1.f;
  entropy::Particle p(inverse_mass, position, velocity, acceleration, damping);

  p.Integrate(1);

  EXPECT_THAT(p.Position(), Eq(Vec3f(10.f, 0.f, 0.f)));
  EXPECT_THAT(p.Velocity(), Eq(Vec3f(10.f, 0.f, 0.f)));
}

TEST_F(ParticleTest, FreeFall_ConstantAccelerationIncreasesVelocity) {
  position = Vec3f(0.f, 100.f, 0.f);
  velocity = force = Vec3f();
  acceleration = Vec3f(0.f, -10.f, 0.f);
  inverse_mass = damping = 1.f;

  entropy::Particle p(inverse_mass, position, velocity, acceleration, damping);

  p.Integrate(1);
  p.Integrate(1);

  EXPECT_THAT(p.Position(), Eq(Vec3f(0.f, 70.f, 0.f)));
  EXPECT_THAT(p.Velocity(), Eq(Vec3f(0.f, -20.f, 0.f)));
}

TEST_F(ParticleTest, SecondLaw_ForcesCorrectlyApplied) {
  position = velocity = acceleration = Vec3f(0.f, 0.f, 0.f);
  force = Vec3f(20.f, 0.f, 0.f);
  inverse_mass = 0.5f;
  damping = 1.f;
  entropy::Particle p(inverse_mass, position, velocity, acceleration, damping);
  p.ApplyForce(force);

  p.Integrate(1);

  EXPECT_THAT(p.Velocity(), Eq(Vec3f(10.f, 0.f, 0.f)));
  EXPECT_THAT(p.Acceleration(), Eq(Vec3f(10.f, 0.f, 0.f)));
}

TEST_F(ParticleTest, InfiniteMass_ImmovableObjectsStayStationary) {
  position = Vec3f(5.f, 5.f, 5.f);
  velocity = Vec3f(0.f, 0.f, 0.f);
  acceleration = Vec3f(0.f, -9.81f, 0.f);
  force = Vec3f(9999.f, 9999.f, 0.f);
  inverse_mass = 0.f;
  damping = 1.f;
  entropy::Particle p(inverse_mass, position, velocity, acceleration, damping);
  p.ApplyForce(force);

  p.Integrate(1);

  EXPECT_THAT(p.Position(), Eq(Vec3f(5.f, 5.f, 5.f)));
  EXPECT_THAT(p.Velocity(), Eq(Vec3f(0.f, 0.f, 0.f)));
}