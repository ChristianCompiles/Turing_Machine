// Module: Transition_Function
// File: Transition_Function.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Transition_Function.cpp implements methods of the class Transition_Function

#include "Transition_Function.h"
#include "Tape_Alphabet.h"
#include "States.h"
#include "Final_States.h"
#include "TM_Utils.h"
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using std::cout;


// Name: load
// Purpose: reads in whitespace delimited tokens,
//          attempting to create syntactically valid transitions;
//          this process occurs until the next keyword is reached or EOF;
//          also ensures that the set of transition functions only
//          contains unique transitions.
void Transition_Function::load(ifstream& definition, bool& valid)
{
    string current_component("transition function");
    string next_keyword("INITIAL_STATE:");

    bool found_keyword = false;

    string source_state;
    char read_char;
    string dest_state;
    char write_char;
    Direction move_direction;

    enum read_state
    {
        reading_from_state,
        reading_read_char,
        reading_dest_state,
        reading_write_char,
        reading_move_dir
    };

    read_state rs = reading_from_state;

    string value;

    while(definition >> value)
    {
        if(uppercase(value) == next_keyword)
        {
            found_keyword = true;
            if (rs != reading_from_state)
                cout << red_start <<"Incomplete transition function\n" << color_reset;
            break;
        }

        switch(rs)
        {
            case reading_from_state:
                source_state = value;
                rs = reading_read_char;
                value.clear();
                break;
            case reading_read_char:
                if(value.length() != 1)
                    cout << yellow_start << "transition function: read char must be single char \"" << value << "\".\n" << color_reset;
                read_char = value[0];
                rs = reading_dest_state;
                value.clear();
                break;
            case reading_dest_state:
                dest_state = value;
                rs = reading_write_char;
                value.clear();
                break;
            case reading_write_char:
                if(value.length() != 1)
                {
                    cout << yellow_start << "transition function: write char must be single char \"";
                    cout << value << "\".\n" << color_reset;
                }
                write_char = value[0];
                rs = reading_move_dir;
                value.clear();
                break;
            case reading_move_dir:
                if(value.length() != 1)
                {
                    cout << yellow_start << "transition function: move char must be single char \"";
                    cout << value << "\".\n" << color_reset;
                }

                if(toupper(value[0]) != 'L' && toupper(value[0]) != 'R')
                {
                    valid = false;
                    cout << yellow_start << "transition function: Invalid move direction \"";
                    cout << value[0] << "\".\n" << color_reset;
                }
                move_direction = (char)toupper(value[0]);

                // push back fully formed transition
                transitions.emplace_back(source_state, read_char, dest_state, write_char, move_direction);
                rs = reading_from_state;
                value.clear();
                break;
        }
    }

    if(!found_keyword)
    {
        cout << red_start << "Did not find keyword \"" << next_keyword;
        cout << "\" following " << current_component << ".\nExiting.\n" << color_reset;
        exit(0);
    }

    // check for duplicates
    int outer_index = 0;
    for(const auto& o : transitions)
    {
        int inner_index = 0;
        for(const auto& i : transitions)
        {
            if((o.source_state()      == i.source_state()) &&
               (o.read_character()    == i.read_character()) &&
               (o.write_character()   == i.write_character()) &&
               (o.destination_state() == i.destination_state()) &&
               (o.move_direction()    == i.move_direction()) &&
               (outer_index           != inner_index))
            {
                cout << yellow_start << "transition function: duplicate found.\n" << color_reset;
                valid = false;
            }
            ++inner_index;
        }
        ++outer_index;
    }
}

// Name: validate
// Purpose: for every transition, validate checks to make sure
//          the source state is not in the set of final states,
//          the source state is in the set of states,
//          the destination state is in the set of states,
//          the read character is in the tape alphabet,
//          the write character is in the tape alphabet
void Transition_Function::validate(const Tape_Alphabet& tape_alphabet, const States& states, const Final_States& final_states, bool& valid) const
{
    for(const auto& i : transitions)
    {
        if(final_states.is_element(i.source_state())) // if source state in set of final states (not ok)
        {
            cout << yellow_start << "tf: source state " << i.source_state() << " is in final states.\n" << color_reset;
            valid = false;
        }

        if(!states.is_element(i.source_state())) // if source state not in set of states (not ok)
        {
            cout << yellow_start << "tf: source state " <<  i.source_state() << " not in set of states.\n" << color_reset;
            valid = false;
        }

        if(!states.is_element(i.destination_state())) // if dest. state not in set of states (not ok)
        {
            cout << yellow_start << "tf: desination state " << i.destination_state() << " not in set of states.\n" << color_reset;
            valid = false;
        }

        if(!tape_alphabet.is_element(i.read_character())) // if read char not in tape alphabet (not ok)
        {
            cout << yellow_start << "tf: read character " << i.read_character() << " not in tape alphabet.\n" << color_reset;
            valid = false;
        }

        if(!tape_alphabet.is_element(i.write_character())) // if write char not in tape alphabet (not ok)
        {
            cout << yellow_start << "tf: write character " << i.write_character() << "not in tape alphabet.\n" << color_reset;
            valid = false;
        }
    }
}

// Name: view
// Purpose: displays the transitions functions
//          in a formatted manner to the console
void Transition_Function::view() const
{
    for(const auto& i : transitions)
    {
        cout << delta << "(" << i.source_state() << ", " << i.read_character() << ") = ";
        cout << "(" << i.destination_state() << ", " << i.write_character() << ", ";
        cout << i.move_direction() << ")\n";
    }
}

// Name: find_transition
// Purpose: given a source state and read charcter,
//          find_transition attempts to find the corresponding transition function,
//          writing to the appropriate inout parameters and setting found to true,
//          otherwise setting found to false
void Transition_Function::find_transition(const string& source_state, char read_character,
                                          string& destination_state, char& write_character,
                                          Direction& move_direction, bool& found)const
{
    for(const auto& i : transitions)
    {
        if((i.source_state() == source_state) && (i.read_character() == read_character))
        {
            destination_state = i.destination_state();
            write_character = i.write_character();
            move_direction = i.move_direction();
            found = true;
            return;
        }
    }
    found = false;
}
