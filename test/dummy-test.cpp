#include <gtest/gtest.h>

class DummyTest : public testing::Test {
 public:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(DummyTest, GivenDummyDataWhenDoingNothingThenSuccess) {
  ASSERT_TRUE(true);
}