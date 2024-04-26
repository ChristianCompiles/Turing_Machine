// Module: Tape_Alphabet
// File: Tape_Alphabet.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Tape_Alphabet.cpp implements the methods of the class Tape_Alphabet

#include "Tape_Alphabet.h"
#include "TM_Utils.h"
#include <string>
using std::string;
using std::endl;

// Name: load
// Purpose: reads in whitespace delimited characters
//          from the TM definition file until the next
//          keyword is read or EOF. It also ensures that
//          every element in the tape alphabet is unique.
void Tape_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;
    string next_keyword("TRANSITION_FUNCTION:");
    string current_component("tape alphabet");
    bool found_keyword = false;

    vector<string> tmp_tape_alphabet;

    while (definition >> value)
    {
        if (uppercase(value) == next_keyword)
        {
            found_keyword = true;
            break;
        }
        tmp_tape_alphabet.push_back(value);
    }

    if (!found_keyword)
    {
        cout << red_start << "Did not find keyword \"" << next_keyword << "\" following " << current_component << ".\nExiting.\n" << color_reset;
        exit(0);
    }

    for (const auto &letter: tmp_tape_alphabet)
    {
        if (letter.length() != 1)
        {
            valid = false;
            cout << yellow_start << "tape alphabet: must be single char \"" << letter << "\".\n" << color_reset;
        }
        else
        {
            if(value[0] != '\\' && value[0] != '[' && value[0] != ']'
               && value[0] != '>' && value [0] != '<' && value[0] >= '!' && value[0] <= '~')
                alphabet.push_back(letter[0]);
            else
            {
                cout << yellow_start << "tape alphabet: invalid char \"" << letter[0] << "\".\n" << color_reset;
            }
        }
    }

    if(alphabet.empty())
    {
        cout << red_start << "Tape alphabet is empty.\nExiting.\n" << color_reset;
        exit(0);
    }

    check_unique_set(alphabet, current_component, valid);
}

// Name: view
// Purpose: displays the elements of the tape alphabet on the console
void Tape_Alphabet::view()
{
    int num_elements = (int)alphabet.size();
    int count = 0;

    cout << gamma << ": {";
    for(const auto &character : alphabet)
    {
        cout << character;
        if(count < num_elements-1)
            cout << ", ";
        count++;
    }
    cout << "}\n";

}

// Name: is_element
// Purpose: checks whether the character passed
//          in is an element of the tape alphabet
bool Tape_Alphabet::is_element(char value) const
{
    bool flag = false;

    for(const auto& i : alphabet)
    {
        if(i == value) // if given string is in set of states
        {
            flag = true;
            break;
        }
    }
    return flag;
}
