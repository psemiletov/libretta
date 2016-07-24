//g++ libretta_linear_interpolator.cpp libretta_linear_interpolator_test.cpp -o libretta_linear_interpolator_test

#include <iostream>

#include "libretta_linear_interpolator.h"

using namespace std;

#define X1 1
#define Y1 15

#define X2 15
#define Y2 1


int main (int argc, char *argv[])
{
 
  CFloatLinearInterpolatorSimple ip (X1, Y1, X2, Y2); 

  
  cout << "-----------" << endl;
 
  cout << "ip.part: " << ip.part << endl;
  
  cout << "-----------" << endl;
 
  
  for (int x = X1; x < X2; x++)
      cout << "x: " << x << " y:" << ip.get_y_at_x (x) << endl;
  
  cout << "-----------" << endl;

  cout << ip.get_y_at_x (X2);  
  
  return 0;
}
