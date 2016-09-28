#include <image.h>
#include "imagetest.h"


imagetest::imagetest(){};

imagetest::~imagetest(){};

void imagetest::SetUp() {};

void imagetest::TearDown() {};

//Tests

TEST_F(imagetest, ComponentImgSizeTest){
  image img;
  EXPECT_EQ(sizeof(img[0]),sizeof(unsigned char));
}

TEST_F(imagetest, ImageFetchTest){
  image img;
  img.getImagePNG("left1.png");
  EXPECT_EQ(img.getWidth(),768);
  EXPECT_EQ(img.getHeight(), 576);
  EXPECT_EQ(sizeof(img[0]), sizeof(unsigned char));
}

TEST_F(imagetest, ImageReturnTest){
  image img;
  img.getImagePNG("left1.png");
  img.outputImagePNG("left1_test.png");
  image img2;
  img2.getImagePNG("left1_test.png");
  EXPECT_EQ(img.getWidth(),img2.getWidth());
  EXPECT_EQ(img.getHeight(),img2.getHeight());
}
