#include "image.h"

//copy Constructor

image::image(const image &img){
  _height = img.getHeight();
  _width = img.getWidth();
  _channels = img.getChannels();
  _bitdepth = img.getBitDepth();
  _data = img.getData();
}

//copy operator

image& image::operator=(const image& img){
  this->_height = img.getHeight();
  this->_width = img.getWidth();
  this->_channels = img.getChannels();
  this->_bitdepth = img.getBitDepth();
  this->_data = img.getData();
}

//file constructor

image::image(const char* infile){
  this->getImagePNG(infile);
}

//file I/O
void image::getImagePNG(const char* infile){
  lodepng::State state;
  std::vector<unsigned char> image;
  std::vector<unsigned char> buffer;
  lodepng::load_file(buffer, infile);

  unsigned error = lodepng::decode(image, _width, _height, state, buffer);
  if(error)
  {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  }
  _channels = lodepng_get_channels(&state.info_png.color);
  _bitdepth = state.info_png.color.bitdepth;
  _data.setVector(image);
}

//NOTE:This function has yet to enable changes in colortype that
// automatically change the image vector conatiner, such as
// supressing alpha channels or getting a mean value to trasnlate the image
// to greyscale
void image::outputImagePNG(const char* outfile){
  lodepng::State state;
  state.info_png.color.bitdepth = _bitdepth;

  switch(_channels){
    case(1):state.info_png.color.colortype = LCT_GREY;
        break;
    case(2):state.info_png.color.colortype = LCT_GREY_ALPHA;
      break;
    case(3):state.info_png.color.colortype = LCT_RGB;
      break;
    case(4):state.info_png.color.colortype = LCT_RGBA;
      break;
  }

  std::vector<unsigned char> png;
  unsigned error = lodepng::encode(png, _data.getVector(), _width, _height, state);
  if(!error) lodepng::save_file(png, outfile);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}
