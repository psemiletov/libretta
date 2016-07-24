/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#include <iostream>
#include <locale> 
#include <iostream>
#include <string>

#include <stdlib.h>

#include "libretta_utils.h"

using namespace std;


size_t str_fuzzy_search (const string &s, const string &text_to_find, size_t start_pos, double q)
{
  size_t counter;
  size_t result = -1; 
  
  bool jump = false;
  
  size_t end_pos = s.length() - 1;
 
  
  for (size_t i = start_pos; i < end_pos; i++)
      {
       if (jump)
	  break;
       
       counter = 0;
       for (int j = 0; j < text_to_find.length(); j++)
           {
            if (s[i + j] == text_to_find[j])
  	       counter++;
	  
          if (get_percent (text_to_find.length(), counter) >= q)
	       {
	        result = i;
		jump = true;
	        break;
	       } 
           }
      }     
   
  return result;
}
