


#ifndef __TOKEN_PARSING_H__
#define __TOKEN_PARSING_H__

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

string read_token(istream& input);

string encode_string(const string& the_string); // Convert a string into a string that will be read as the original string by "read_token".

char* get_c_str(const string& the_string); // Form a C string from the current string.

#endif


