#ifndef IMGCHANNEL_H
#define IMGCHANNEL_H

/** \brief Image class destined to be a container for decoded images as a
 *      as 3 matrix of channels.
 *
 * The  type determines in this occasion the size of the channel
 * The container should allow to access elements individually in random access or
 * continuously, as well as moving the information, obtained through the usage of
 * the matrix class
 */

#include <matrix.h>
#include <lodepng.h>

template <typename T>
class imgChannel {
public:
  //Constructors
  imgChannel();
  imgChannel(int height, int width);
  imgChannel(const imgChannel &im);
  ~imgChannel(){};

  //Image Load from file
  virtual void loadImagePNG(const char* infile);
  //Image Channels to file
  virtual void returnImagePNG(const char* outfile);

  inline void setHeight(int h){_height = h;}
  inline void setWidth(int w){_width = w;}
  inline const int getHeight() const {return _height;}
  inline const int getWidth() const {return _width;}

  inline const matrix<T>& getRed() const {return &_red; }
  inline const matrix<T>& getGreen() const {return &_green; }
  inline const matrix<T>& getBlue() const {return &_blue; }

  //operators
  imgChannel & operator=(const imgChannel &);

private:

  //matrix containing each of the RGB channels
  matrix<T> _red;
  matrix<T> _green;
  matrix<T> _blue;
  int _height;
  int _width;
  int _pxlform;


};

#endif // IMGCHANNEL_H
