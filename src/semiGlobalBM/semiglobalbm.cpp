#include "semiglobalbm.h"

semiGlobalBM::semiGlobalBM(const semiGlobalBMParams & params, const image & left, const image & right, image & dispmap,std::vector<CostType> & buffer){
  _params = params;
  _left = left;
  _right = right;
  _dispmap = dispmap;
  _buffer = buffer;
}


void semiGlobalBM::pxlCostBT(const image & img1, const image & img2, int row, int minD, int maxD, std::vector<CostType>::iterator & cost, std::vector<PxlType>::iterator & buffer, const std::vector<PxlType>::iterator & lookupTab,int tabOfs, int ftzero)
{
  int x,c, width = img1.getWidth(), channels = img1.getChannels();
  int minX1 = std::max(maxD, 0), maxX1 = width + std::min(minD, 0);
  int minX2 = std::max(minX1 - maxD, 0), maxX2 = std::min(maxX1 - minD, width);
  int D = maxD - minD, width1 = maxX1 - minX1, width2 = maxX2 - minX2;

  //iterators preparation
  std::vector<PxlType>::const_iterator rowit1 = img1.getData().getVector().cbegin() + row*width*channels;
  std::vector<PxlType>::const_iterator rowit2 = img2.getData().getVector().cbegin() + row*width*channels;
  std::vector<PxlType>::iterator prowit1 = buffer + width2*2;
  std::vector<PxlType>::iterator prowit2 = prowit1 + width*channels*2;
  std::vector<PxlType>::iterator buffit = buffer;
  std::vector<CostType>::iterator costit = cost;

  std::vector<PxlType>::const_iterator tabit = lookupTab + tabOfs;

  for(c = 0; c<channels*2; c++)
  {
    prowit1[width*c] = prowit1[width*c + width-1] = prowit2[width*c] = prowit2[width*c +width-1] =tabit[0];
  }
  int n1 = row > 0 ? -img1.getBitDepth()*width*channels/8 : 0, s1 = row < img1.getHeight()-1 ? img1.getBitDepth()*width*channels/8 : 0;
  int n2 = row > 0 ? -img2.getBitDepth()*width*channels/8 : 0, s2 = row < img2.getHeight()-1 ? img1.getBitDepth()*width*channels/8 : 0;

  if( channels == 1 )
  {
    for( x = 1; x < width-1; x++ )
    {
        prowit1[x] = tabit[(rowit1[x+1] - rowit1[x-1])*2 + rowit1[x+n1+1] - rowit1[x+n1-1] + rowit1[x+s1+1] - rowit1[x+s1-1]];
        prowit2[width-1-x] = tabit[(rowit2[x+1] - rowit2[x-1])*2 + rowit2[x+n2+1] - rowit2[x+n2-1] + rowit2[x+s2+1] - rowit2[x+s2-1]];

        prowit1[x+width] = rowit1[x];
        prowit2[width-1-x+width] = rowit2[x];
    }
  }
  else
  {
    for( x = 1; x < width-1; x++ )
    {
      prowit1[x] = tabit[(rowit1[x*3+3] - rowit1[x*3-3])*2 + rowit1[x*3+n1+3] - rowit1[x*3+n1-3] + rowit1[x*3+s1+3] - rowit1[x*3+s1-3]];
      prowit1[x+width] = tabit[(rowit1[x*3+4] - rowit1[x*3-2])*2 + rowit1[x*3+n1+4] - rowit1[x*3+n1-2] + rowit1[x*3+s1+4] - rowit1[x*3+s1-2]];
      prowit1[x+width*2] = tabit[(rowit1[x*3+5] - rowit1[x*3-1])*2 + rowit1[x*3+n1+5] - rowit1[x*3+n1-1] + rowit1[x*3+s1+5] - rowit1[x*3+s1-1]];

      prowit2[width-1-x] = tabit[(rowit2[x*3+3] - rowit2[x*3-3])*2 + rowit2[x*3+n2+3] - rowit2[x*3+n2-3] + rowit2[x*3+s2+3] - rowit2[x*3+s2-3]];
      prowit2[width-1-x+width] = tabit[(rowit2[x*3+4] - rowit2[x*3-2])*2 + rowit2[x*3+n2+4] - rowit2[x*3+n2-2] + rowit2[x*3+s2+4] - rowit2[x*3+s2-2]];
      prowit2[width-1-x+width*2] = tabit[(rowit2[x*3+5] - rowit2[x*3-1])*2 + rowit2[x*3+n2+5] - rowit2[x*3+n2-1] + rowit2[x*3+s2+5] - rowit2[x*3+s2-1]];

      prowit1[x+width*3] = rowit1[x*3];
      prowit1[x+width*4] = rowit1[x*3+1];
      prowit1[x+width*5] = rowit1[x*3+2];

      prowit2[width-1-x+width*3] = rowit2[x*3];
      prowit2[width-1-x+width*4] = rowit2[x*3+1];
      prowit2[width-1-x+width*5] = rowit2[x*3+2];
    }
  }

  //cost.resize(width1*D, 0);
  for(int i = 0; i<width1*D; i++) cost[i] = 0;
  //simplfy costs within the lookupTab
  buffit -= minX2;
  costit -= minX1*D + minD;


  for( c = 0; c < channels*2; c++, prowit1 += width, prowit2 += width )
  {
    int diff_scale = c < channels ? 0 : 2;
    // precompute
    //   v0 = min(row2[x-1/2], row2[x], row2[x+1/2]) and
    //   v1 = max(row2[x-1/2], row2[x], row2[x+1/2]) and
    for( x = minX2; x < maxX2; x++ )
    {
        int v = prowit2[x];
        int vl = x > 0 ? (v + prowit2[x-1])/2 : v;
        int vr = x < width-1 ? (v + prowit2[x+1])/2 : v;
        int v0 = std::min(vl, vr); v0 = std::min(v0, v);
        int v1 = std::max(vl, vr); v1 = std::max(v1, v);
        buffit[x] = static_cast<PxlType>(v0);
        buffit[x + width2] = static_cast<PxlType>(v1);
    }

    for( x = minX1; x < maxX1; x++ )
    {
      int u = prowit1[x];
      int ul = x > 0 ? (u + prowit1[x-1])/2 : u;
      int ur = x < width-1 ? (u + prowit1[x+1])/2 : u;
      int u0 = std::min(ul, ur); u0 = std::min(u0, u);
      int u1 = std::max(ul, ur); u1 = std::max(u1, u);

      for( int d = minD; d < maxD; d++ )
      {
        int v = prowit2[width-x-1 + d];
        int v0 = buffit[width-x-1 + d];
        int v1 = buffit[width-x-1 + d + width2];
        int c0 = std::max(0, u - v1); c0 = std::max(c0, v0 - u);
        int c1 = std::max(0, v - u1); c1 = std::max(c1, u0 - v);

        costit[x*D + d] = static_cast<short>(cost[x*D+d] + (std::min(c0, c1) >> diff_scale));
      }
    }
  }
}

void semiGlobalBM::disparitySGBM(const image & img1, const image & img2, image & disp1, const semiGlobalBMParams & params, std::vector<CostType> & buffer)
{
  const int ALIGN = 16;
  const int DISP_SHIFT = DISPARITY_SHIFT;
  const int DISP_SCALE = (1 << DISP_SHIFT);
  const CostType MAX_COST = SHRT_MAX;

  int minD = params.minDisparity, maxD = minD + params.numDisparities;
  SADWindowSize sws;
  sws.width = sws.height = params.SADWindowSize > 0 ? params.SADWindowSize: 5;
  int ftzero = std::max(params.preFilterCap, 15) | 1;
  int uniquenessRatio = params.uniquenessRatio >= 0 ? params.uniquenessRatio : 10;
  int disp12MaxDiff = params.disp12MaxDiff > 0 ? params.disp12MaxDiff : 1;
  int P1 = params.P1 > 0 ? params.P1 : 2, P2 = std::max(params.P2 > 0 ? params.P2 : 5, P1+1);
  int k, width = disp1.getWidth(), height = disp1.getHeight();
  int minX1 = std::max(maxD, 0), maxX1 = width + std::min(minD, 0);
  int D = maxD - minD, width1 = maxX1 - minX1;
  int INVALID_DISP = minD - 1, INVALID_DISP_SCALED = INVALID_DISP*DISP_SCALE;
  int SW2 = sws.width/2, SH2 = sws.height/2;
  bool fullDP = params.mode == Mode::MODE_HH;
  int npasses = fullDP ? 2 : 1;
  const int TAB_OFS = 256*4, TAB_SIZE = 256 + TAB_OFS*2;
  std::vector<PxlType> clipTab(TAB_SIZE);

  //might be more easy to read to use auto clipTabit = clipTab.begin();
  //also might be in c++0x
  //for (decltype(l)::iterator it = l.begin(), end = l.end(); it != end; ++it)
  //being l a predeclared STL style  container such as a list
  std::vector<PxlType>::iterator clipTabit;

  for( clipTabit = clipTab.begin(); clipTabit != clipTab.end(); ++clipTabit)
    *clipTabit = static_cast<PxlType> (std::min(std::max(k - TAB_OFS, -ftzero), ftzero) + ftzero);

  if( minX1 >= maxX1 )
  {
    //if the disparity is invalid it return a single pixel image
    disp1.setWidth(1); disp1.setHeight(1);disp1.setChannels(4);disp1.setBitDepth(8);
    disp1.getData().getVector().assign(static_cast<std::size_t>(disp1.getWidth()*disp1.getHeight()*disp1.getChannels()*disp1.getBitDepth()/8), INVALID_DISP_SCALED);
    return;
  }
  //Check the value of Disparity D
  if (D % 16 != 0)
  {
    //TODO:THROW EXCEPTION
  }


  // NR - the number of directions. the loop on x below that computes Lr assumes that NR == 8.
  // if you change NR, please, modify the loop as well.
  int D2 = D+16, NRD2 = NR2*D2;

  // the number of L_r(.,.) and min_k L_r(.,.) lines in the buffer:
  // for 8-way dynamic programming we need the current row and
  // the previous row, i.e. 2 rows in total
  const int NLR = 2;
  const int LrBorder = NLR - 1;
  // for each possible stereo match (img1(x,y) <=> img2(x-d,y))
  // we keep pixel difference cost (C) and the summary cost over NR directions (S).
  // we also keep all the partial costs for the previous line L_r(x,d) and also min_k L_r(x, k)
  std::size_t costBufSize = width1*D;
  std::size_t CSBufSize = costBufSize*(fullDP ? height : 1);
  std::size_t minLrSize = (width1 + LrBorder*2)*NR2, LrSize = minLrSize*D2;
  int hsumBufNRows = SH2*2 + 2;
  std::size_t totalBufSize = (LrSize + minLrSize)*NLR*sizeof(CostType) + // minLr[] and Lr[]
  costBufSize*(hsumBufNRows + 1)*sizeof(CostType) + // hsumBuf, pixdiff
  CSBufSize*2*sizeof(CostType) + // C, S
  width*16*img1.getChannels()*sizeof(PxlType) + // temp buffer for computing per-pixel cost
  width*(sizeof(CostType) + sizeof(PxlType)) + 1024; // disp2cost + disp2

  // whereas OpenCV uses a single buffer, in pursuit of comprehensibility
  // these buffers will be separated in types.
  // Buffer size is nonoptimized

  buffer.assign(totalBufSize,1);
   //NON ALIGNED
   //TODO:ALIGN THE BUFFER FOR VECTORIZATION
  std::vector<CostType>::iterator Cbufit = buffer.begin();
  std::vector<CostType>::iterator Sbufit = Cbufit + CSBufSize;
  std::vector<CostType>::iterator hsumBufit = Sbufit + CSBufSize;
  std::vector<CostType>::iterator pixDiffit = hsumBufit + costBufSize*hsumBufNRows;

  std::vector<CostType>::iterator disp2costit = pixDiffit +costBufSize+(LrSize + minLrSize)*NLR;
  //this buffer is from disptype. Beign disptype and cost type both shorts, i include it in the same buffer
  std::vector<CostType>::iterator disp2ptrit = disp2costit + width;

  std::vector<PxlType> tmpbuf(width);
  decltype(tmpbuf)::iterator tmpbufit = tmpbuf.begin();

  for( k = 0; k < width1*D; k++ )
    Cbufit[k] = static_cast<CostType> (P2);
  //The usage of the value P2 saves calculations withn the loop

  for( int pass = 1; pass <= npasses; pass++ )
  {
    int x1, y1, x2, y2, dx, dy;

    if( pass == 1 )
    {
      y1 = 0; y2 = height; dy = 1;
      x1 = 0; x2 = width1; dx = 1;
    }
    else
    {
      y1 = height-1; y2 = -1; dy = -1;
      x1 = width1-1; x2 = -1; dx = -1;
    }

    //originally vector<CostType*>, this buffers collect memory directions
    std::vector<CostType> cost;
    std::vector<std::vector<CostType>::iterator> Lr(NLR/*,0*/), minLr(NLR/*,0*/);
    decltype(Lr)::iterator Lrit = Lr.begin();
    decltype(minLr)::iterator minLrit = minLr.begin();

    for( k = 0; k < NLR; k++ )
    {
      // shift Lr[k] and minLr[k] pointers, because we allocated them with the borders,
      // and will occasionally use negative indices with the arrays
      // we need to shift Lr[k] pointers by 1, to give the space for d=-1.
      // however, then the alignment will be imperfect, i.e. bad for SSE,
      // thus we shift the pointers by 8 (8*sizeof(short) == 16 - ideal alignment)
      // pixdiffit is pxltype and lrit is costtype
      Lrit[k] = pixDiffit + costBufSize + LrSize*k + NRD2*LrBorder + 8;
      //memset( Lr[k] - LrBorder*NRD2 - 8, 0, LrSize*sizeof(CostType) );
      //We do the same usign the iterator continuously
      fill(Lrit[k] - LrBorder*NRD2 - 8, Lrit[k] - LrBorder*NRD2 - 8 + LrSize, 0);
      minLrit[k] = pixDiffit + costBufSize + LrSize*NLR + minLrSize*k + NR2*LrBorder;
      //memset( minLr[k] - LrBorder*NR2, 0, minLrSize*sizeof(CostType) );
      fill(minLrit[k] - LrBorder*NR2, minLrit[k] - LrBorder*NR2 + minLrSize, 0);
    }
    for( int y = y1; y != y2; y += dy )
    {
      int x, d;
      std::vector<PxlType>::iterator disp1ptr = disp1.getData().getVector().begin() + y * width;
      std::vector<CostType>::iterator C = Cbufit + (!fullDP ? 0 : y*costBufSize);
      std::vector<CostType>::iterator S = Sbufit + (!fullDP ? 0 : y*costBufSize);

      if( pass == 1 ) // compute C on the first pass, and reuse it on the second pass, if any.
      {
        int dy1 = y == 0 ? 0 : y + SH2, dy2 = y == 0 ? SH2 : dy1;

        for( k = dy1; k <= dy2; k++ )
        {
          std::vector<CostType>::iterator hsumAddit = hsumBufit + (std::min(k, height-1) % hsumBufNRows)*costBufSize;

          if( k < height )
          {
            pxlCostBT( img1, img2, k, minD, maxD, pixDiffit, tmpbufit, clipTabit, TAB_OFS, ftzero );

            //memset(hsumAdd, 0, D*sizeof(CostType));
            fill(hsumAddit, hsumAddit+D, 0);
            for( x = 0; x <= SW2*D; x += D )
            {
              int scale = x == 0 ? SW2 + 1 : 1;
              for( d = 0; d < D; d++ )
                hsumAddit[d] = static_cast<CostType>(hsumAddit[d] + pixDiffit[x + d]*scale);
            }

            if( y > 0 )
            {
              const std::vector<CostType>::iterator hsumSub = hsumBufit + (std::max(y - SH2 - 1, 0) % hsumBufNRows)*costBufSize;
              const std::vector<CostType>::iterator Cprev = !fullDP || y == 0 ? C : C - costBufSize;

              for( x = D; x < width1*D; x += D )
              {
                const std::vector<CostType>::iterator pixAdd = pixDiffit + std::min(x + SW2*D, (width1-1)*D);
                const std::vector<CostType>::iterator pixSub = pixDiffit + std::max(x - (SW2+1)*D, 0);
                {
                  for( d = 0; d < D; d++ )
                  {
                    int hv = hsumAddit[x + d] = static_cast<CostType>(hsumAddit[x - D + d] + pixAdd[d] - pixSub[d]);
                    C[x + d] = static_cast<CostType>(Cprev[x + d] + hv - hsumSub[x + d]);
                  }
                }
              }
            }
            else
            {
              for( x = D; x < width1*D; x += D )
              {
                const std::vector<CostType>::iterator pixAdd = pixDiffit + std::min(x + SW2*D, (width1-1)*D);
                const std::vector<CostType>::iterator pixSub = pixDiffit + std::max(x - (SW2+1)*D, 0);

                for( d = 0; d < D; d++ )
                  hsumAddit[x + d] = static_cast<CostType>(hsumAddit[x - D + d] + pixAdd[d] - pixSub[d]);
              }
            }
          }
          if( y == 0 )
          {
            int scale = k == 0 ? SH2 + 1 : 1;
            for( x = 0; x < width1*D; x++ )
              C[x] = static_cast<CostType>(C[x] + hsumAddit[x]*scale);
          }
        }
        // also, clear the S buffer
        for( k = 0; k < width1*D; k++ )
          S[k] = 0;
      }

      // clear the left and the right borders
      /*
      memset( Lr[0] - NRD2*LrBorder - 8, 0, NRD2*LrBorder*sizeof(CostType) );
      memset( Lr[0] + width1*NRD2 - 8, 0, NRD2*LrBorder*sizeof(CostType) );
      memset( minLr[0] - NR2*LrBorder, 0, NR2*LrBorder*sizeof(CostType) );
      memset( minLr[0] + width1*NR2, 0, NR2*LrBorder*sizeof(CostType) );
      */
      fill(Lrit[0] - NRD2*LrBorder - 8, Lrit[0] - NRD2*LrBorder - 8 + NRD2*LrBorder, 0);
      fill(Lrit[0] + width1*NRD2 - 8, Lrit[0] + width1*NRD2 - 8 + NRD2*LrBorder, 0);
      fill(minLrit[0] - NR2*LrBorder, minLrit[0] - NR2*LrBorder + NR2*LrBorder, 0);
      fill(minLrit[0] + width1*NR2,minLrit[0] + width1*NR2 + NR2*LrBorder, 0);
      /*
      [formula 13 in the paper]
      compute L_r(p, d) = C(p, d) +
      min(L_r(p-r, d),
      L_r(p-r, d-1) + P1,
      L_r(p-r, d+1) + P1,
      min_k L_r(p-r, k) + P2) - min_k L_r(p-r, k)
      where p = (x,y), r is one of the directions.
      we process all the directions at once:
      0: r=(-dx, 0)
      1: r=(-1, -dy)
      2: r=(0, -dy)
      3: r=(1, -dy)
      4: r=(-2, -dy)
      5: r=(-1, -dy*2)
      6: r=(1, -dy*2)
      7: r=(2, -dy)
      */

      for( x = x1; x != x2; x += dx )
      {
        int xm = x*NR2, xd = xm*D2;

        int delta0 = minLrit[0][xm - dx*NR2] + P2, delta1 = minLrit[1][xm - NR2 + 1] + P2;
        int delta2 = minLrit[1][xm + 2] + P2, delta3 = minLrit[1][xm + NR2 + 3] + P2;

        std::vector<CostType>::iterator Lr_p0 = Lrit[0] + xd - dx*NRD2;
        std::vector<CostType>::iterator Lr_p1 = Lrit[1] + xd - NRD2 + D2;
        std::vector<CostType>::iterator Lr_p2 = Lrit[1] + xd + D2*2;
        std::vector<CostType>::iterator Lr_p3 = Lrit[1] + xd + NRD2 + D2*3;

        Lr_p0[-1] = Lr_p0[D] = Lr_p1[-1] = Lr_p1[D] =
        Lr_p2[-1] = Lr_p2[D] = Lr_p3[-1] = Lr_p3[D] = MAX_COST;

        std::vector<CostType>::iterator Lr_p = Lrit[0] + xd;
        const std::vector<CostType>::iterator Cp = C + x*D;
        std::vector<CostType>::iterator Sp = S + x*D;
        {
          int minL0 = MAX_COST, minL1 = MAX_COST, minL2 = MAX_COST, minL3 = MAX_COST;

          for( d = 0; d < D; d++ )
          {
            int Cpd = Cp[d], L0, L1, L2, L3;

            L0 = Cpd + std::min((int)Lr_p0[d], std::min(Lr_p0[d-1] + P1, std::min(Lr_p0[d+1] + P1, delta0))) - delta0;
            L1 = Cpd + std::min((int)Lr_p1[d], std::min(Lr_p1[d-1] + P1, std::min(Lr_p1[d+1] + P1, delta1))) - delta1;
            L2 = Cpd + std::min((int)Lr_p2[d], std::min(Lr_p2[d-1] + P1, std::min(Lr_p2[d+1] + P1, delta2))) - delta2;
            L3 = Cpd + std::min((int)Lr_p3[d], std::min(Lr_p3[d-1] + P1, std::min(Lr_p3[d+1] + P1, delta3))) - delta3;

            Lr_p[d] = (CostType)L0;
            minL0 = std::min(minL0, L0);

            Lr_p[d + D2] = (CostType)L1;
            minL1 = std::min(minL1, L1);

            Lr_p[d + D2*2] = (CostType)L2;
            minL2 = std::min(minL2, L2);

            Lr_p[d + D2*3] = (CostType)L3;
            minL3 = std::min(minL3, L3);

            Sp[d] = saturate_cast<CostType>(Sp[d] + L0 + L1 + L2 + L3);
          }
          minLrit[0][xm] = (CostType)minL0;
          minLrit[0][xm+1] = (CostType)minL1;
          minLrit[0][xm+2] = (CostType)minL2;
          minLrit[0][xm+3] = (CostType)minL3;
        }
      }
      if( pass == npasses )
      {
        for( x = 0; x < width; x++ )
        {
          disp1ptr[x] = disp2ptrit[x] = static_cast<DispType>(INVALID_DISP_SCALED);
          disp2costit[x] = MAX_COST;
        }

        for( x = width1 - 1; x >= 0; x-- )
        {
          std::vector<CostType>::iterator Sp = S + x*D;
          int minS = MAX_COST, bestDisp = -1;

          if( npasses == 1 )
          {
            int xm = x*NR2, xd = xm*D2;

            int minL0 = MAX_COST;
            int delta0 = minLrit[0][xm + NR2] + P2;
            std::vector<CostType>::iterator Lr_p0 = Lrit[0] + xd + NRD2;
            Lr_p0[-1] = Lr_p0[D] = MAX_COST;
            std::vector<CostType>::iterator Lr_p = Lrit[0] + xd;

            const std::vector<CostType>::iterator Cp = C + x*D;
            {
              for( d = 0; d < D; d++ )
              {
                int L0 = Cp[d] + std::min((int)Lr_p0[d], std::min(Lr_p0[d-1] + P1, std::min(Lr_p0[d+1] + P1, delta0))) - delta0;

                Lr_p[d] = static_cast<CostType>(L0);
                minL0 = std::min(minL0, L0);

                int Sval = Sp[d] = saturate_cast<CostType>(Sp[d] + L0);
                if( Sval < minS )
                {
                  minS = Sval;
                  bestDisp = d;
                }
              }
              minLrit[0][xm] = static_cast<CostType>(minL0);
            }
          }
          else
          {
            {
              for( d = 0; d < D; d++ )
              {
                int Sval = Sp[d];
                if( Sval < minS )
                {
                  minS = Sval;
                  bestDisp = d;
                }
              }
            }
          }
          for( d = 0; d < D; d++ )
          {
          if( Sp[d]*(100 - uniquenessRatio) < minS*100 && std::abs(bestDisp - d) > 1 )
            break;
          }
          if( d < D )
            continue;
          d = bestDisp;
          int _x2 = x + minX1 - d - minD;
          if( disp2costit[_x2] > minS )
          {
            disp2costit[_x2] = static_cast<CostType>(minS);
            disp2ptrit[_x2] = static_cast<DispType>(d + minD);
          }

          if( 0 < d && d < D-1 )
          {
            // do subpixel quadratic interpolation:
            //   fit parabola into (x1=d-1, y1=Sp[d-1]), (x2=d, y2=Sp[d]), (x3=d+1, y3=Sp[d+1])
            //   then find minimum of the parabola.
            int denom2 = std::max(Sp[d-1] + Sp[d+1] - 2*Sp[d], 1);
            d = d*DISP_SCALE + ((Sp[d-1] - Sp[d+1])*DISP_SCALE + denom2)/(denom2*2);
          }
          else
            d *= DISP_SCALE;
          disp1ptr[x + minX1] = static_cast<DispType>(d + minD*DISP_SCALE);
        }

        for( x = minX1; x < maxX1; x++ )
        {
          // we round the computed disparity both towards -inf and +inf and check
          // if either of the corresponding disparities in disp2 is consistent.
          // This is to give the computed disparity a chance to look valid if it is.
          int d1 = disp1ptr[x];
          if( d1 == INVALID_DISP_SCALED )
            continue;
          int _d = d1 >> DISP_SHIFT;
          int d_ = (d1 + DISP_SCALE-1) >> DISP_SHIFT;
          int _x = x - _d, x_ = x - d_;
          if( 0 <= _x && _x < width && disp2ptrit[_x] >= minD && std::abs(disp2ptrit[_x] - _d) > disp12MaxDiff &&
            0 <= x_ && x_ < width && disp2ptrit[x_] >= minD && std::abs(disp2ptrit[x_] - d_) > disp12MaxDiff )
            disp1ptr[x] = static_cast<DispType>(INVALID_DISP_SCALED);
        }
      }

      // now shift the cyclic buffers
      std::swap( Lrit[0], Lrit[1] );
      std::swap( minLrit[0], minLrit[1] );
    }
  }
}
//copied as is from OpenCV
void semiGlobalBM::compute()
{
  /*CV_INSTRUMENT_REGION()*/

  /*Mat left = leftarr.getMat(), right = rightarr.getMat();
  CV_Assert( left.size() == right.size() && left.type() == right.type() &&
             left.depth() == CV_8U );

  disparr.create( left.size(), CV_16S );
  Mat disp = disparr.getMat();*/

  std::vector<CostType> buffer;

/*if(params.mode==MODE_SGBM_3WAY)
    computeDisparity3WaySGBM( left, right, disp, params, buffers, num_stripes );
  else*/
  semiGlobalBM::disparitySGBM( _left, _right, _dispmap, _params, buffer);


/*medianBlur(disp, disp, 3);*/
/*
  if( params.speckleWindowSize > 0 )
    filterSpeckles(disp, (params.minDisparity - 1)*StereoMatcher::DISP_SCALE, params.speckleWindowSize,
                     StereoMatcher::DISP_SCALE*params.speckleRange, buffer);
*/
}
