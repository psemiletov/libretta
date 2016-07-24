//g++ libretta_utils.cpp libretta_utils_test.cpp -o libretta_utils_test

#include <iostream>
#include <string>
#include <vector>


#include "libretta_utils.h"


using namespace std;

int main (int argc, char *argv[])
{
  vector <string> v = files_get_list (current_path(), ".txt");
 
  for (const auto &t: v)
    {  
     cout << t << endl;
     
    }
  
 
  return 0;
}
