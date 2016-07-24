//g++ libretta_calc.cpp libretta_calc_test.cpp -o libretta_calc_test

#include <iostream>
#include "libretta_calc.h"

using namespace std;

int main (int argc, char *argv[])
{
//  cout << calculate ("(5+3)*3)") << endl;

  cout << "type the expression or \"exit\" and press Enter to execute" << endl;

  string value;

  do
    {
     cin >> value;
     cout << calculate (value) << endl;
    }
  while (value != "exit");

  
  return 0;
}
