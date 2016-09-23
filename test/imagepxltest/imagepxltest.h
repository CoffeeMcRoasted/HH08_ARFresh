#ifndef IMAGEPXLTEST_H
#define IMAGEPXLTEST_H

#include "gtest/gtest.h"

//Fixture for testing class Matrix
class imagepxltest : public ::testing::Test {
protected:
  imagepxltest();

  //For clean-up work that doesn't throw exceptions
  virtual ~imagepxltest();

  //For further set-up and clean-up necessities we define
  //Code called inmediately before each test
  virtual void SetUp();
  //Code called inmediately after each test
  virtual void TearDown();

};
#endif // IMAGEPXLTEST_H
