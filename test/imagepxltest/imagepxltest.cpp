#include <imgpxl.h>
#include "imagepxltest.h"


imagepxltest::imagepxltest(){};

imagepxltest::~imagepxltest(){};

void imagepxltest::SetUp() {};

void imagepxltest::TearDown() {};

//Tests

TEST_F(imagepxltest, ComponentImgSizeTest){
  imgPxl<unsigned char> img;
  EXPECT_EQ(sizeof(img[0]),sizeof(unsigned char));
}

TEST_F(imagepxltest, ImageFetchTest){
  imgPxl<unsigned char> img;
  img.loadImagePNG("left1.png");
  EXPECT_EQ(img.getWidth(),768);
  EXPECT_EQ(img.getHeight(), 576);
  EXPECT_EQ(sizeof(img[0]), sizeof(unsigned char));
}

TEST_F(imagepxltest, ImageReturnTest){
  imgPxl<unsigned char> img;
  img.loadImagePNG("left1.png");
  img.returnImagePNG("left1_test.png");
  imgPxl<unsigned char> img2;
  img2.loadImagePNG("left1_test.png");
  EXPECT_EQ(img.getWidth(),img2.getWidth());
  EXPECT_EQ(img.getHeight(),img2.getHeight());
}
