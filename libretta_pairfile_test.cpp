//g++ libretta_pairfile.cpp libretta_pairfile_test.cpp -o libretta_pairfile_test
//read ones - default values, another time from ./pairfile.conf

#include <iostream>
#include "libretta_pairfile.h"


using namespace std;

int main (int argc, char *argv[])
{
  CPairFile  pf ("./pairfile.conf");

  int i = pf.get_int ("int_key", 13);
  float f = pf.get_float ("float_key", 777.7);
  string s = pf.get_string ("string_key", "hello world");

  cout << "i = " << i << endl;
  cout << "f = " << f << endl;
  cout << "s = " << s << endl;
  
  pf.set_int ("int_key", 14);
  pf.set_float ("float_key", 555.5);
  pf.set_string ("string_key", "hi");
  
  pf.save();
  
  
  CPairFile  pf2 ("a=1\nb=2\nc=3", true);

  int i2 = pf2.get_int ("a", 13);
  float f2 = pf2.get_float ("b", 777.7);
  string s2 = pf2.get_string ("c", "hello world");

  
  cout << "i2 = " << i2 << endl;
  cout << "f2 = " << f2 << endl;
  cout << "s2 = " << s2 << endl;

  
  return 0;
}
