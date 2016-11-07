#ifndef IMAGE_H
#define IMAGE_H

/** \brief Image class destined to be a container for decoded images as a
 *      as a single matrix of unsigned char elements.
 *
 *
 * The container should allow to access elements individually in random access or
 * continuously, as well as moving the information, obtained through the usage of
 * the matrix class
 */

#include <matrix.h>
#include "lodepng.h"
#include <iostream>

class image{
public:
  //constructors
  image(){}
  image(unsigned int height, unsigned int width):_height{height},_width{width}{
    _data.resize(height,width*_channels*_bitdepth/8);
  }
  image(const image &img);
  image(const char* infile);
  virtual ~image(){}

  //operators
  //the operator () gives access to the especified element of the pixel
  //NOTE This is a temporal version of the function, would need to correct
  //    for bitdepth less than 8

  const unsigned char & operator()(unsigned int row, unsigned int col, unsigned int channel = 1){
    return _data(row, (col*_channels*_bitdepth/8)+(channel-1)*_bitdepth/8);
  }

  const unsigned char & operator[](unsigned int n){return _data[n];}

  image& operator=(const image&);

  //access
  inline const unsigned int getHeight() const {return _height;}
  inline const unsigned int getWidth() const{return _width;}
  inline const unsigned int getChannels() const{return _channels;}
  inline const unsigned int getBitDepth() const{return _bitdepth;}
  inline const matrix<unsigned char>& getData() const{return _data;}
  inline matrix<unsigned char>& getData(){return _data;}

  //value setting. Always resizes after setting

  void setHeight(unsigned int height){_height = height;this->resize();}
  void setWidth(unsigned int width){_width = width;this->resize();}
  void setChannels(unsigned int channels){_channels = channels;this->resize();}
  void setBitDepth(unsigned int bitdepth){_bitdepth = bitdepth;this->resize();}
  //void setData(const matrix<unsigned char>& mat);

  //Image I/O to files
  void getImagePNG(const char* infile);
  void outputImagePNG(const char* outfile);

private:
  //Initialized to be an 8bit per channel RGBA image
  unsigned int _height = 0;
  unsigned int _width = 0;
  unsigned int _channels = 4;
  unsigned int _bitdepth = 8;
  matrix<unsigned char> _data;
  //Not compiling
  //std::vector<unsigned char>::iterator _dataIt = _data.getVector().begin();

  inline void resize(){_data.resize(_height,_width*_channels*_bitdepth/8);}
};

#endif //IMAGE_H
