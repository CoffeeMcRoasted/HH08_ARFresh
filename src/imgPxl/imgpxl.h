#ifndef IMGPXL_H
#define IMGPXL_H

/** \brief Image class destined to be a container for decoded images as a
 *      as a single matrix of pixels.
 *
 *
 * The container should allow to access elements individually in random access or
 * continuously, as well as moving the information, obtained through the usage of
 * the matrix class
 */


#include <matrix.h>
#include "lodepng.h"
#include <iostream>

struct pixelRGB{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

struct pixelRGBA{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
};

template<typename T>
class imgPxl
{
public:
  //Constructors
  imgPxl(){}
  imgPxl(int height, int width);
  imgPxl(const imgPxl &im);
  ~imgPxl(){}

  //Image Load from file
  void loadImagePNG(const char* infile){
  std::vector<unsigned char> v;
  unsigned int width , height;
  unsigned error = lodepng::decode(v,width,height,infile);
  if (error) std::cout<<"decoder error "<< error << ": " <<
    lodepng_error_text(error)<<std::endl;
  this->setWidth(width);
  this->setHeight(height);
  _pixels.setVector(v);
  std::cout << width<<" "<<height << std::endl;
}

  //Pixel Matrix to Image
  //void returnImagePNG(const char* outfile);

  inline void setHeight(int h){_height = h;}
  inline void setWidth(int w){_width = w;}
  inline void setChannels(int n) {_channels = n;}
  inline const int getHeight() const {return _height;}
  inline const int getWidth() const {return _width;}
  inline const int getChannels() const{return _channels;}
  inline const matrix<T>& getPixels() const {return &_pixels;}

  //operators
  imgPxl & operator=(const imgPxl&);
  imgPxl & operator()(int row, int col);
  T& operator[](int n){return _pixels[n];}


private:
  matrix<T> _pixels;
  unsigned int _height = 0;
  unsigned int _width = 0;
  unsigned int _channels = 0;
};
#endif // IMGPXL_H
