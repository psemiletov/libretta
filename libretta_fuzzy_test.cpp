#include <iostream>
#include "libretta_fuzzy.h"

using namespace std;

int main (int argc, char *argv[])
{
  string txt = "doggy kitty moose huldufolk cybertron foobar";

  cout << "the source text is" << endl;
  cout << "-----------------------------------------" << endl;

  cout << txt << endl;

  cout << "-----------------------------------------" << endl;
  
  cout << "type the text to find or \"exit\" and press Enter to search" << endl;

  string value;

  do
    {
     cin >> value;
     size_t i = str_fuzzy_search (txt, value, 0, 50);
     cout << i << endl;
    }
  while (value != "exit");

  
  return 0;
}
