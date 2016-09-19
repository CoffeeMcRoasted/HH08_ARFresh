#include <matrix.h>
#include <matrixtest.h>

using ::testing::Return;

matrixtest::matrixtest(){};

matrixtest::~matrixtest(){};

void matrixtest::SetUp() {};

void matrixtest::TearDown() {};

//Tests

TEST_F(matrixtest, ComponentMatrixSizeTest){
  matrix<char> mat;
  EXPECT_EQ(sizeof(mat[0]),sizeof(char));
}
