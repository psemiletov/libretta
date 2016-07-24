//g++ libretta_string_utils.cpp libretta_string_utils_test.cpp -o libretta_string_utils_test

#include <iostream>
#include <string>
#include <vector>


#include "libretta_string_utils.h"


using namespace std;

int main (int argc, char *argv[])
{

 // string s = string_file_load (argv[1]);
  //cout << s << endl; 
 
  vector<string> v = string_split ("a\nb\nc\n", '\n');
 
  cout << v[0] << endl;
  cout << v[1] << endl;
  cout << v[2] << endl;
  
  return 0;
}
