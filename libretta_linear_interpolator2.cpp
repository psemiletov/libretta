#include "libretta_linear_interpolator2.h"

#include <cmath>

CFloatLinearInterpolator::CFloatLinearInterpolator (float val1, float val2, size_t val1pos, size_t val2pos)
{
  value1 = val1;
  value2 = val2;
  
  size_t elements_between = val2pos - val1pos;
  
  if (value2 > value1)
     {
      float values_diff = value2 - value1;
 
      if (values_diff == 0)
         part = 0;
      else
           part = (float) values_diff / elements_between;
     }
   else  
     {
      float values_diff = value1 - value2;
 
      if (values_diff == 0)
         part = 0;
      else
           part = (float) values_diff / elements_between;
     }     
}


float CFloatLinearInterpolator::get_value_at_pos (size_t pos)
{
  if (value2 > value1)
      return pos * part;
  else
      return fabs (pos * part - value1);
   
}

