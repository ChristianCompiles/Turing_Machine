// Module: Final_States
// File: Final_States.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Final_states.cpp implements methods for the class Final_States

#include "Final_States.h"
#include "TM_Utils.h"
using std::endl;

// Name: load
// Purpose: reads in whitespace delimited strings until EOF is reached
//          and ensures that every element of final states is unique
void Final_States::load(ifstream& definition, bool& valid)
{
    string value;
    string current_component("FINAL_STATES");

   while(definition >> value)
   {
       names.push_back(value);
   }

   check_unique_set(names, current_component, valid);
}

// Name: validate
// Purpose: ensures that all final states are in the TM's set of states
void Final_States::validate(const States& states, bool& valid)
{
    for(const auto& i : names)
    {
        if(!states.is_element(i))
        {
            valid = false;
            cout << yellow_start <<  "final states: \"" << i << "\" not in set of states.\n" << color_reset << endl;
        }
    }
}

// Name: view
// Purpose: displays the final states to the console
void Final_States::view()
{
    int num_final_states = (int)names.size();
    int count = 0;

    cout << "F: {";
    for(const auto &state : names)
    {
        cout << state;
        if(count < num_final_states-1)
            cout << ", ";
        ++count;
    }
    cout << "}\n";
}

// Name: is_elements
// Purpose: checks if the state passed to it is in the set of states
bool Final_States::is_element(const string& value) const
{
    bool flag = false;

    for(const auto& final_state : names)
    {
        if(final_state == value) // if given string is in set of states
        {
            flag = true;
            break;
        }
    }
    return flag;
}
