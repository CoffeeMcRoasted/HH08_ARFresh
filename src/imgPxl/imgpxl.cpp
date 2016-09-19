#include <imgpxl.h>

//Constructors
//Copy

template <typename T>
imgPxl<T>::imgPxl(const imgPxl &im){
  _height = im.getHeight();
  _width = im.getWidth();
  _pixels = im.getPixels();
}

//operators
//copy assingment
template <typename T>
imgPxl<T> & imgPxl<T>::operator = (const imgPxl &im){
  _height = im.getHeight();
  _width = im.getWidth();
  _pixels = im.getPixels();
  return *this;
}

//template <typename T>
//void imgPxl<T>::loadImage
