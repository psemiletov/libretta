/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#include <string>
#include <sstream>
#include <vector>

#include "libretta_string_utils.h"


vector<string> &split (const string &s, char delim)
{
  vector<string> result;
  stringstream stream (s);
  string line;
  
  while (getline (stream, line, delim)) 
       {
        result.push_back (line);
       }
  
  return result;
}

