#include "semiglobalbm.h"

int main(int argc, char const *argv[]) {
  /* code */
  image left("left1.png");
  image right("right1.png");
  image dispmap(left.getHeight(),left.getWidth());
  dispmap.setChannels(1); dispmap.setBitDepth(16);
  semiGlobalBMParams params(-39,144,7,0,0,0,0,0,0,0,MODE_SGBM);
  std::vector<CostType> buffer;
  semiGlobalBM* sgbm = new semiGlobalBM(params, left, right, dispmap, buffer);

  sgbm->compute();
  sgbm->outDispMap("dispmap.png");

  delete sgbm;
  return 0;
}
