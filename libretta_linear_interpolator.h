#ifndef LIBRETTA_LINEAR_INTERPOLATOR_H
#define LIBRETTA_LINEAR_INTERPOLATOR_H

using namespace std;

#include <cstddef>

class CFloatLinearInterpolator
{
public:
 
  float y1;
  float y2;

  size_t x1;
  size_t x2;
 
  
  CFloatLinearInterpolator (size_t x_1, float y_1, size_t x_2, float y_2);

  virtual float get_y_at_x (size_t x) {};
 
};

class CFloatLinearInterpolatorSimple: public CFloatLinearInterpolator
{
public:
    
  float values_diff; 
  float part;
  
  
  CFloatLinearInterpolatorSimple (size_t x_1, float y_1, size_t x_2, float y_2);

  float get_y_at_x (size_t x);
};

#endif