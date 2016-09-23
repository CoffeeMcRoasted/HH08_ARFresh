#include <matrix.h>
#include "matrixtest.h"


matrixtest::matrixtest(){};

matrixtest::~matrixtest(){};

void matrixtest::SetUp() {};

void matrixtest::TearDown() {};

//Tests

TEST_F(matrixtest, ComponentMatrixSizeTest){
  matrix<unsigned char> mat;
  EXPECT_EQ(sizeof(mat[0]),sizeof(unsigned char));
}
