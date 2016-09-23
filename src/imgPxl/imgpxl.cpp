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


//only works if T is unsigned char
//results in 4 bytes per pixel ordered RGBA
/*
template <typename T>
void imgPxl<T>::loadImagePNG(const char* infile){
  unsigned error = lodepng::decode(_pixels.getVector(),_width,_height,infile);
  if (error) std::cout<<"decoder error "<< error << ": " <<
    lodepng_error_text(error)<<std::endl;
}
*/
