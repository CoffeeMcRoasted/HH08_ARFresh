#include <semiglobalbm.h>
#include "stereotest.h"


stereotest::stereotest(){};

stereotest::~stereotest(){};

void stereotest::SetUp() {};

void stereotest::TearDown() {};

//Tests

TEST_F(stereotest, StereoTest){
  image left("left1.png");
  image right("right1.png");
  image dispmap(left.getHeight(),left.getWidth());
  dispmap.setChannels(1); dispmap.setBitDepth(16);
  semiGlobalBMParams params(-39,144,7);
  std::vector<CostType> buffer_;
  semiGlobalBM sgbm(params, left, right, dispmap, buffer)

  void compute();
  void outDispMap("dispmap.png")
  EXPECT_EQ(left.getWidth(),dispmap.getWidth());
  EXPECT_EQ(left.getHeight(), dispmap.getHeight());
}
