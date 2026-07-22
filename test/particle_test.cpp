#include "engine/particle.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

class ParticleTest : public testing::Test {
 public:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(
    ParticleTest,
    GivenMovingParticleWhenNoForcesAreAppliedThenItKeepsMovingWithConstantVelocity) {
  entropy::Particle p(1.f, Vec3f(), Vec3f(10.f, 0.f, 0.f), Vec3f(), 1.f,
                      Vec3f());

  p.Integrate(1);

  ASSERT_THAT(p.GetPosition(), Eq(Vec3f(10.f, 0.f, 0.f)));
  ASSERT_THAT(p.GetVelocity(), Eq(Vec3f(10.f, 0.f, 0.f)));
}