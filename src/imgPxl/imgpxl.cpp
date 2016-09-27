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

template <typename T>
void imgPxl<T>::loadImagePNG(const char* infile){
std::vector<unsigned char> v;
unsigned int width , height;
unsigned error = lodepng::decode(v,width,height,infile);
if (error) std::cout<<"decoder error "<< error << ": " <<
  lodepng_error_text(error)<<std::endl;
this->setWidth(width);
this->setHeight(height);
_pixels.setVector(v);
}

//solution to linking error as suggested in:
//https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
template void imgPxl<unsigned char>::loadImagePNG(const char* infile);
