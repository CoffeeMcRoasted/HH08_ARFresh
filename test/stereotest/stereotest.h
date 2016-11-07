#ifndef STEREOTEST_H
#define STEREOTEST_H

#include "gtest/gtest.h"

//Fixture for testing class Matrix
class stereotest : public ::testing::Test {
protected:
  stereotest();

  //For clean-up work that doesn't throw exceptions
  virtual ~stereotest();

  //For further set-up and clean-up necessities we define
  //Code called inmediately before each test
  virtual void SetUp();
  //Code called inmediately after each test
  virtual void TearDown();

};
#endif // STEREOTEST_H
