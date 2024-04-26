// Module: Tape
// File: Tape.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Tape.cpp implements the methods of the class Tape

#include "Tape.h"
#include "TM_Utils.h"

// Name: Tape
// Purpose: This constructor intializes tape, current cell, and blank character
Tape::Tape(): cells(" "), current_cell(0), blank_character(' '){}

// Name: load
// Purpose: loads blank TM definition file and ensures that next string read in is next keyword
void Tape::load(ifstream& definition, bool& valid)
{
    string value;
    string current_component("BLANK_CHARACTER:");
    string next_keyword("FINAL_STATES:");

    if((definition >> value) && (value.length() == 1)
    && value[0] != '\\' && value[0] != '[' && value[0] != ']'
    && value[0] != '>' && value [0] != '<' && value[0] >= '!' && value[0] <= '~')
        blank_character = value[0];
    else
    {
        cout << "Illegal blank_character.\n";
        valid = false;
    }
    if((!(definition >> value)) || (uppercase(value) != next_keyword))
    {
        cout << red_start << "Did not find keyword \"" << next_keyword << "\" following " << current_component << ".\nExiting.\n" << color_reset;
        valid = false;
        exit(0);
    }
}

// Name: validate
// Purpose: checks to make sure blank character
//          is not in input alphabet and is in tape alphabet
void Tape::validate(const Input_Alphabet& input_alphabet, const Tape_Alphabet& tape_alphabet, bool& valid) const
{
    if(input_alphabet.is_element(blank_character)) // if blank char in input alphabet (not ok)
    {
        cout << yellow_start << "Blank character " << blank_character << " is element of input alphabet\n" << color_reset;
        valid = false;
    }
    if(!tape_alphabet.is_element(blank_character)) // if blank char not in tape alphabet (not ok)
    {
        cout << yellow_start << "Blank character " << blank_character << " not in tape alphabet\n" << color_reset;
        valid = false;
    }
}

// Name: view
// Purpose: displays blank character to console
void Tape::view()const
{
    cout << "B: " << blank_character << "\n";
}

// Name: initialize
// Purpose: initializes tape to the input string that is passed in
void Tape::initialize(const string& input_string)
{
    cells = input_string + blank_character;
    current_cell = 0;
}

// Name: update
// Purpose: update writes the passed in character to
//          the current position of the tape head and
//          attempts to move the tape head left or right,
//          throwing an exception if the tape head attempts
//          to move to the left of the starting cell
void Tape::update(char write_character, Direction move_direction)
{
    move_direction = (char)toupper(move_direction);

    if((move_direction == 'L') && (current_cell == 0)) // cannot move left of start cell (will crash)
    {
        throw Crash("Left move from first cell");
    }
    if(move_direction == 'R' && (current_cell == cells.length() - 1)) // will need to extend TM tape
    {
        cells += blank_character;
    }

    cells[current_cell] = write_character;

    if(move_direction == 'L')
        --current_cell;
    else
        ++current_cell;
}

// Name: left
// Purpose: displays up to maximum_number_of_cells
//          to the left of the tape head, adding
//          truncation symbol '<' if truncation occured
string Tape::left(int maximum_number_of_cells) const
{
    int first_cell = std::max(0, current_cell-maximum_number_of_cells);
    string value = cells.substr(first_cell, current_cell - first_cell);

    if(value.length() < maximum_number_of_cells)
    {
        value.insert(0, "<");
    }
    return value;
}

// Name: right
// Purpose: displays up to maximum_number_of_cells
//          to the right of the tape head, including the tape head,
//          adding truncation symbol '>' if truncation occured
string Tape::right(int maximum_number_of_cells) const
{
    int end_cell = (int)cells.length() - 1;

    while((end_cell >= current_cell) && (cells[end_cell] == blank_character)) // get to non-blank character
        --end_cell;

    int last_cell = std::min(end_cell, current_cell+maximum_number_of_cells-1);

    string value = cells.substr(current_cell, last_cell-current_cell+1);

    if(value.length() < end_cell-current_cell+1)
    {
        value.append(">");
    }

    return value;
}

// Name: current_character
// Purpose: return the character at position of tape head
char Tape::current_character() const
{
    return cells[current_cell];
}
