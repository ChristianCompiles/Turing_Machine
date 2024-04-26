#include "TM_Utils.h"

// Name: uppercase
// Purpose: convert string to upper case
string uppercase(const string& value)
{
    string to_return;
    for(const auto& i : value)
    {
        to_return.push_back((char)toupper(i));
    }
    return to_return;
}

// Name: parse_string_to_int
// Purpose: checks to make sure the string
//          passed in only contains positive integers;
//          returns 0 if invalid string,
//          else returns integer from string
int parse_string_to_int(const string& to_parse)
{
    bool only_digits = true;

    if(to_parse.empty())
        return 0;

    for(int i = 0; i < to_parse.length(); i++)
    {
        if(isdigit(to_parse[i]))
        {
            continue;
        }
        else
        {
            if((i == 0) && (to_parse[i] == 45)) // if the first char is dash (negative), that's ok
            {continue;}
            only_digits = false;
            break;
        }
    }

    if(!only_digits)
    {
        cout << "only accept integers\n";
        return 0;
    }

    int actual_num = stoi(to_parse);

    if(actual_num < 1)
    {
        cout << "must be >= 1\n";
        return 0;
    }
    else
        return actual_num;
}
