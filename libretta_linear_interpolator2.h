#ifndef LIBRETTA_LINEAR_INTERPOLATOR_H
#define LIBRETTA_LINEAR_INTERPOLATOR_H

using namespace std;

#include <cstddef>

class CFloatLinearInterpolator
{
public:
  
  float value1;
  float value2;
 
  float part;
  
  CFloatLinearInterpolator (float val1, float val2, size_t val1pos, size_t val2pos);
  float get_value_at_pos (size_t pos);
};

#endif