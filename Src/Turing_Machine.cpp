// Module: Turing_Machine
// File: Turing_Machine.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Turine_Machine.cpp provides the implementation of methods for the class Turing_Machine.

#include "Turing_Machine.h"
#include "TM_Utils.h"

// Name: Turing_Machine
// Purpose: this constructor reads in the definition file
//          and validates the definition.
Turing_Machine::Turing_Machine(const string& definition_file_name)
{
    valid = true;
    used = false;
    operating = false;
    accepted = false;
    rejected = false;

    definition.open(definition_file_name);
    if(!definition.is_open())
    {
        cout << "Could not open: " + definition_file_name << endl;
        exit(0);
    }

    string value;
    string first_keyword("STATES:");
    bool found_keyword = false;
    string accumulator_str;
    string prev_str;
    char cur_char;

    while(definition.get(cur_char))
    {
        if(isspace(cur_char))
        {
            if(uppercase(accumulator_str) == first_keyword)
            {
                found_keyword = true;

                if(!prev_str.empty() && prev_str.back() != '\n')
                    description.emplace_back("\n");
                break;
            }
            accumulator_str.append(1, cur_char);
            prev_str = accumulator_str;
            description.push_back(accumulator_str);
            accumulator_str.clear();
        }
        else
            accumulator_str.append(1, cur_char);
    }

    if(!found_keyword)
    {
        cout << red_start << "Did not find keyword \"" << first_keyword << "\" following description.\nExiting.\n" << color_reset;
        exit(0);
    }

    states.load(definition, valid);
    input_alphabet.load(definition, valid);
    tape_alphabet.load(definition, valid);
    transition_function.load(definition, valid);

    // read in initial state
    string second_keyword("BLANK_CHARACTER:");

    vector<string> tmp_initial_state_vec;
    bool found_initial_state_keyword = false;
    while(definition >> value)
    {
        if(uppercase(value) == second_keyword)
        {
            found_initial_state_keyword = true;
            break;
        }
        tmp_initial_state_vec.push_back(value);
    }

    if(!found_initial_state_keyword)
        cout << red_start << "Did not find keyword \"" << second_keyword << "\".\nExiting.\n" << color_reset;

    if(tmp_initial_state_vec.size() != 1)
    {
        cout << "Initial states: must have one initial state\n";
        valid = false;
    }

    if(tmp_initial_state_vec.size() == 1)
        initial_state = tmp_initial_state_vec.at(0);

    current_state = initial_state;

    tape.load(definition, valid);
    final_states.load(definition, valid);

    // validate sequence
    input_alphabet.validate(tape_alphabet, valid);
    final_states.validate(states, valid);
    tape.validate(input_alphabet, tape_alphabet, valid);
    transition_function.validate(tape_alphabet, states, final_states, valid);

    // validate initial state in set of states
    if(!states.is_element(initial_state))
    {
        valid = false;
        cout << yellow_start << "initial state: \"" << initial_state << "\" not in set of states.\n" << color_reset;
    }

    if(!valid)
        exit(0);
}

// Name: view_definition
// Purpose: displays white-space preserved description of definition,
//          followed by a formatted, formal definition of TM
void Turing_Machine::view_definition()
{
    // view TM description
    for(const auto &i : description) // print description from 'this' first
    {
        cout << i;
    }
    cout << endl;

    states.view();
    input_alphabet.view();
    tape_alphabet.view();
    transition_function.view();
    cout << "Q_0: " << this->initial_state << endl; // displaying initial state
    tape.view();
    final_states.view();
}

// Name: view_instantaneous_description
// Purpose: view maximum_number_of_cells to the left and right of the tape head
void Turing_Machine::view_instantaneous_descriptions(int maximum_number_of_cells)
{
    cout << total_number_of_transitions() << " ";
    cout << tape.left(maximum_number_of_cells);
    cout << "[" << current_state << "]";
    cout << tape.right(maximum_number_of_cells);
    cout << endl;
}

// Name: intialize
// Purpose: set beginning of tape to input string, intialize values
void Turing_Machine::initialize(const string& input_string)
{
    number_of_transitions = 0;
    tape.initialize(input_string);
    original_input_string = input_string;
}

// Name: perform_transitions
// Purpose: perform up to maximum_number_of_transitions
void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
    if(!operating)
    {
        accepted = false;
        rejected = false;
        operating = true;
        current_state = initial_state;
    }
    used = true;

    char read_char = tape.current_character();
    string destination_state;
    char write_char;
    Direction move_direction;
    bool found;

    if(final_states.is_element(current_state)) // check if in final state w/o any transitions
    {
        accepted = true;
        return;
    }

    for(int i = 0; i < maximum_number_of_transitions; i++)
    {
        transition_function.find_transition(current_state, read_char, destination_state, write_char, move_direction, found);
        if(found)
        {
            tape.update(write_char, move_direction);
            current_state = destination_state;
            read_char = tape.current_character();
            ++number_of_transitions;
            if(final_states.is_element(current_state))
            {
                accepted = true;
                operating = false;
                return;
            }
        }
        else // crash
        {
            rejected = true;
            operating = false;
            throw(Crash("Could not find transition.\n"));
        }
    }
}

// Name: terminate_operation
// Purpose: set all possible statuses of TM to false
void Turing_Machine::terminate_operation()
{
    operating = false;
    accepted = false;
    rejected = false;
}

// Name: input_string
// Purpose: returns class member variable: original_input_string
string Turing_Machine::input_string()
{
    return original_input_string;
}

// Name: total_number_of_transitions
// Purpose: returns class member variable: number_of_transitions
int Turing_Machine::total_number_of_transitions() const
{
    return number_of_transitions;
}

// Name: is_valid_definition
// Purpose: returns class member variable: valid
bool Turing_Machine::is_valid_definition() const
{
    return valid;
}

// Name: is_valid_input_string
// Purpos: check if string value is solely composed
//         of characters from input alphabet
bool Turing_Machine::is_valid_input_string(const string& value) const
{
    bool str_valid = true;
    for(const auto& i : value)
    {
        if(!input_alphabet.is_element(i)) // char in string not in input alphabet
        {
            cout << yellow_start << "input string: char \"" << i << "\" not in input alphabet.\n" << color_reset;
            str_valid = false;
        }
    }
    return str_valid;
}

// Name: is_used
// Purpose: returns class member variable: is_used
bool Turing_Machine::is_used() const {return used;}

// Name: is_operating
// Purpose: returns class member variable: operating
bool Turing_Machine::is_operating() const {return operating;}

// Name: is_accepted_input_string
// Purpose: returns class member variable: accepted
bool Turing_Machine::is_accepted_input_string() const {return accepted;}

// Name: is_rejected_input_string
// Purpose: returns class member variable: rejected
bool Turing_Machine::is_rejected_input_string() const {return rejected;}
