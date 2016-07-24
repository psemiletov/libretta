//g++ libretta_linear_interpolator.cpp libretta_linear_interpolator_test.cpp -o libretta_linear_interpolator_test

#include <iostream>

#include "libretta_linear_interpolator2.h"

using namespace std;

#define VALUE2 15

int main (int argc, char *argv[])
{
 
  CFloatLinearInterpolator ip (1.0f, 10.0f, 1, VALUE2); 
  
//  CFloatLinearInterpolator ip (10.0f, 1.0f, 1, VALUE2); 

  
  cout << "-----------" << endl;
 
  cout << "ip.part: " << ip.part << endl;
  
  cout << "-----------" << endl;
 
  
  for (int i = 1; i <= VALUE2; i++)
      cout << ip.get_value_at_pos (i) << endl;
  
  cout << "-----------" << endl;
 
  return 0;
}
