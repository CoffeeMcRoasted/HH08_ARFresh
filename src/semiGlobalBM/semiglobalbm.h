#ifndef SEMIGLOBALBM_H
#define SEMIGLOBALBM_H

/** \brief Class destined to be a container for the semiglobal matching algorithm
 *
 * The algorithm and the pertinent structures for the variables are contained within
 */

#include "image.h"
#include <climits>
#include "saturatecast.h"

typedef unsigned char PxlType;
typedef short CostType;
typedef short DispType;

//Parameter Structure as used by the original OpenCV version without mode selection
enum Mode{
  MODE_SGBM = 1,
  MODE_HH = 2
};
enum { NR = 16, NR2 = NR/2 };

struct semiGlobalBMParams
{
    semiGlobalBMParams()
    {
        minDisparity = numDisparities = 0;
        SADWindowSize = 0;
        P1 = P2 = 0;
        disp12MaxDiff = 0;
        preFilterCap = 0;
        uniquenessRatio = 0;
        speckleWindowSize = 0;
        speckleRange = 0;
        mode = Mode::MODE_SGBM;
    }

    semiGlobalBMParams( int _minDisparity, int _numDisparities, int _SADWindowSize,
                      int _P1, int _P2, int _disp12MaxDiff, int _preFilterCap,
                      int _uniquenessRatio, int _speckleWindowSize, int _speckleRange, int _mode)
    {
        minDisparity = _minDisparity;
        numDisparities = _numDisparities;
        SADWindowSize = _SADWindowSize;
        P1 = _P1;
        P2 = _P2;
        disp12MaxDiff = _disp12MaxDiff;
        preFilterCap = _preFilterCap;
        uniquenessRatio = _uniquenessRatio;
        speckleWindowSize = _speckleWindowSize;
        speckleRange = _speckleRange;
        mode = _mode;
    }

    int minDisparity;
    int numDisparities;
    int SADWindowSize;
    int preFilterCap;
    int uniquenessRatio;
    int P1;
    int P2;
    int speckleWindowSize;
    int speckleRange;
    int disp12MaxDiff;
    int mode;
};

struct SADWindowSize{
  int width;
  int height;
};
//obtained from stereomatcher code
enum  	{
  DISPARITY_SHIFT = 4
};

class semiGlobalBM{
public:
  semiGlobalBM(){};
  semiGlobalBM(const semiGlobalBMParams & params, const image & left, const image & right, image & dispmap,std::vector<CostType> & buffer);
  ~semiGlobalBM(){};



  void outDispMap(const char* Outfile){_dispmap.outputImagePNG(Outfile);}
  void compute();

  void disparitySGBM(const image & img1, const image & img2, image & disp1, const semiGlobalBMParams & params, std::vector<CostType> & buffer );
  void pxlCostBT(const image & img1, const image & img2, int row, int minD, int maxD, std::vector<CostType>::iterator & cost,std::vector<PxlType>::iterator & buffer, const std::vector<PxlType>::iterator & lookupTab,int tabOfs, int ftzero);
  inline void getImagePNGRight(const char* infile){_right.getImagePNG(infile);}
  inline void getImagePNGLeft(const char* infile){_left.getImagePNG(infile);}

private:
  semiGlobalBMParams _params;
  image _left;
  image _right;
  image _dispmap;
  std::vector<CostType> _buffer;
};

/*!
 *  Aligns pointer by the certain number of bytes
 *
 *  This small inline function aligns the pointer by the certain number of bytes by shifting
 *  it forward by 0 or a positive offset.
 */
template<typename T> inline T* alignPtr(T* ptr, size_t n=sizeof(T))
{
    return (T*)(((size_t)ptr + n-1) & -n);
}

#endif //SEMIGLOBALBM_H
