// Module: States
// File: States.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// States.cpp implements the methods of the class States

#include "States.h"
#include "TM_Utils.h"
#include <algorithm>

// Name: load
// Purpose: reads whitespace delimited strings
//          from the TM definition file until
//          the next keyword is read in or EOF
//          and ensures that every element in
//          set of states is unique
void States::load(ifstream& definition, bool& valid)
{
    string value;
    string current_component("states");
    string next_keyword("INPUT_ALPHABET:");
    bool found_keyword = false;

    while(definition >> value)
    {
        if (uppercase(value) == next_keyword)
        {
            found_keyword = true;
            break;
        }
        names.push_back(value);
    }

    if(!found_keyword)
    {
        cout << red_start << "Did not find keyword \"" << next_keyword << "\" following "<< current_component << ".\nExiting.\n" << color_reset;
        exit(0);
    }
    else if(names.empty())
    {
        cout << red_start << "Set of states is empty.\nExiting.\n" << color_reset;
        exit(0);
    }
    for(const auto& state : names) // iterate over collected states
    {
        for(const auto& letter : state)// make sure all characters of state name are ok
        {
            if((letter>=65 && letter <= 90) || (letter >= 97 && letter <= 122) || (letter >= 48 && letter <= 57) || (letter == 45) || (letter == 95))
                continue; // char is valid
            else
            {
                cout << yellow_start "states: invalid char '" << letter << "' in state \"" << state << "\"\n" << color_reset;
                valid = false;
            }
        }
    }
    check_unique_set(names, current_component, valid);
}

// Name: view
// Purpose: displays the states of the TM on the console
void States::view()
{
    int num_states = (int)names.size();
    int count = 0;

    cout << "Q: {";
    for(const auto &state : names)
    {
        cout << state;
        if(count < num_states - 1)
            cout << ", ";
        ++count;
    }
    cout << "}\n";
}

// Name: is_element
// Purpose: checks whether the state passed in is in the TM's set of states
bool States::is_element(const string& value) const
{
    bool flag = false;

    for(const auto& i : names)
    {
        if(i == value) // if given string is in set of states
        {
            flag = true;
            break;
        }
    }
    return flag;
}
