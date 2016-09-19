#ifndef MATRIXTEST_H
#define MATRIXTEST_H

#include "gtest/gtest.h"

//Fixture for testing class Matrix
class matrixtest : public ::testing::Test {
protected:
  matrixtest();

  //For clean-up work that doesn't throw exceptions
  virtual ~matrixtest();

  //For further set-up and clean-up necessities we define
  //Code called inmediately before each test
  virtual void SetUp();
  //Code called inmediately after each test
  virtual void TearDown();

}
#endif // MATRIXTEST_H
