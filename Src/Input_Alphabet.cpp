// Module: Input_Alphabet
// File: Input_Alphabet.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Input_Alphabet.cpp implements the methods of the class Input_Alphabet

#include "Input_Alphabet.h"
#include "TM_Utils.h"

// Name: load
// Purpose: reads whitespaced delimited characters until the next keyword is read or EOF
//          and ensures that every element of the input alphabet is unique
void Input_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;
    string next_keyword("TAPE_ALPHABET:");
    string current_component("input alphabet");
    bool found_keyword = false;

    vector<string> tmp_input_alphabet;

    while (definition >> value)
    {
        if (uppercase(value) == next_keyword)
        {
            found_keyword = true;
            break;
        }
        tmp_input_alphabet.push_back(value);
    }

    if (!found_keyword)
    {
        cout << red_start << "Did not find keyword \"" << next_keyword << "\" following " << current_component << ".\nExiting.\n" << color_reset;
        exit(0);
    }

    for (const auto &letter: tmp_input_alphabet)
    {
        if (letter.length() != 1)
        {
            valid = false;
            cout << yellow_start << "input alphabet: must be single char \"" << letter << "\".\n" << color_reset;
        }
        else
        {
            if(value[0] != '\\' && value[0] != '[' && value[0] != ']'
               && value[0] != '>' && value [0] != '<' && value[0] >= '!' && value[0] <= '~')
            alphabet.push_back(letter[0]);
            else
            {
                cout << yellow_start << "input alphabet: invalid char \"" << letter[0] << "\".\n" << color_reset;
            }
        }
    }
    check_unique_set(alphabet, current_component, valid);
}

// Name: view
// Purpose: displays the characters of the input alphabet to the console
void Input_Alphabet::view()
{
    int num_states = (int)alphabet.size();
    int count = 0;

    cout << sigma << ": {";
    for(const auto &character : alphabet)
    {
        cout << character;
        if(count < num_states - 1)
            cout << ", ";
        ++count;
    }
    cout << "}\n";
}

// Name: validate
// Purpose: ensures that every element of the input alphabet is a member of the tape alphabet
void Input_Alphabet::validate(const Tape_Alphabet& tape_alphabet, bool& valid)
{
    for(const auto& i : alphabet)
    {
        if(!tape_alphabet.is_element(i))
        {
            valid = false;
            cout << yellow_start << "input alphabet: \"" << i << "\" is not member of tape alphabet.\n" << color_reset;
        }
    }
}

// Name: is_elements
// Purpose: checks if the character passed to it is in the input alphabet
bool Input_Alphabet::is_element(char value) const
{
    for(const auto& i : alphabet)
    {
        if(i == value) // if given char is in input alphabet
            return true;
    }
    return false; // char never appeared in input alphabet
}
