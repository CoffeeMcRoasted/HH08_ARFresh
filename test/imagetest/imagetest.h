#ifndef IMAGETEST_H
#define IMAGETEST_H

#include "gtest/gtest.h"

//Fixture for testing class Matrix
class imagetest : public ::testing::Test {
protected:
  imagetest();

  //For clean-up work that doesn't throw exceptions
  virtual ~imagetest();

  //For further set-up and clean-up necessities we define
  //Code called inmediately before each test
  virtual void SetUp();
  //Code called inmediately after each test
  virtual void TearDown();

};
#endif // IMAGETEST_H
