// Module: TM_utils
// File: TM_utils.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// TM_utils.h defines type Direction, and defines various output modifiers (Greek characters, colors);
// implements helper functions to check uniqueness of elements
// and convert string to uppercase

#ifndef UNIQUE_SET_H
#define UNIQUE_SET_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "TM_Utils.h"
using std::cout;
using std::count;
using std::vector;
using std::string;

// define type Direction (char)
typedef char Direction;

// define Greek character codes
#define sigma "\u03A3"
#define gamma "\u0393"
#define delta "\u03B4"

// define command line color codes
#define red_start "\033[1;31m"
#define yellow_start "\033[1;33m"
#define color_reset "\033[1;0m"

// check if a vector of elements has any duplicates and set valid to false if so
template<class T>
void check_unique_set(vector<T>& vec, const string& current_component, bool&valid)
{
    int index = 0;
    for(const auto& i : vec)
    {
        if(std::count(vec.begin(), vec.end(), i) > 1)
        {
            cout << yellow_start << current_component << ": duplicate found \"" << i << "\".\n" << color_reset;
            valid = false;
            vec.erase(vec.begin()+index); // remove element so duplicate doesn't get picked up twice
        }
        index++;
    }
}

// convert string to upper case
string uppercase(const string& value);

// checks to make sure the string passed in only contains integers
int parse_string_to_int(const string& to_parse);

#endif
