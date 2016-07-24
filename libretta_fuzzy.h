/***********************************************************
 *   this code by Peter Semiletov is Public Domain         *
 **********************************************************/

#ifndef LIBRETTA_UTILS_H
#define LIBRETTA_UTILS_H


#include <string>


using namespace std;

size_t str_fuzzy_search (const string &s, const string &text_to_find, size_t start_pos, double q);

#endif