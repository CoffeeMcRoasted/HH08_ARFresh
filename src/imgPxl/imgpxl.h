#ifndef IMGPXL_H
#define IMGPXL_H

/** \brief Image class destined to be a container for decoded images as a
 *      as a single matrix of pixels.
 *
 * The container should allow to access elements individually in random access or
 * continuously, as well as moving the information, obtained through the usage of
 * the matrix class
 */


#include <matrix.h>
#include <lodepng.h>

struct pixelRGB{
  char red;
  char green;
  char blue;
};

struct pixelRGBA{
  char red;
  char green;
  char blue;
  char alpha;
};

template<typename T>
class imgPxl
{
public:
  //Constructors
  imgPxl();
  imgPxl(int height, int width);
  imgPxl(const imgPxl &im);
  ~imgPxl(){}

  //Image Load from file
  virtual void loadImage(const char* infile);
  //Pixel Matrix to Image
  virtual void returnImage(const char* outfile);

  inline void setHeight(int h){_height = h;}
  inline void setWidth(int w){_width = w;}
  inline const int getHeight() const {return _height;}
  inline const int getWidth() const {return _width;}
  inline const matrix<T>& getPixels() const {return &_pixels; }

  //operators
  imgPxl & operator=(const imgPxl&);

private:
  matrix<T> _pixels;
  int _height;
  int _width;
  int _pxlform;

};
#endif // IMGPXL_H
