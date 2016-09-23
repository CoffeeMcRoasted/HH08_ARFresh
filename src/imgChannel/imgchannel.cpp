#include <imgchannel.h>

//Constructors
//Copy

template <typename T>
imgChannel<T>::imgChannel(const imgChannel &im){
  _height = im.getHeight();
  _width = im.getWidth();
  _red = im.getRed();
  _green = im.getGreen();
  _blue = im.getBlue();
}

//operators
//copy assingment
template <typename T>
imgChannel<T> & imgChannel<T>::operator = (const imgChannel &im){
  _height = im.getHeight();
  _width = im.getWidth();
  _red = im.getRed();
  _green = im.getGreen();
  _blue = im.getBlue();
  return *this;
}

//template <typename T>
//void imgChannel<T>::loadImage
