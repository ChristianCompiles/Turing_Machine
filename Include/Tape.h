// Module: Tape
// File: Tape.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Tape.h provides the private members and public declarations
// for the class Tape

#ifndef TAPE_H
#define TAPE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Tape_Alphabet.h"
#include "Input_Alphabet.h"
#include "TM_Utils.h"
#include "Crash.h"
using std::string;
using std::ifstream;
using std::cout;

class Tape
{
private:
    string cells;
    int current_cell;
    char blank_character;

public:
    Tape();
    void load(ifstream& definition, bool& valid);
    void validate(const Input_Alphabet& input_alphabet, const Tape_Alphabet& tape_alphabet, bool& valid) const;
    void view()const;
    void initialize(const string& input_string);
    void update(char write_character, Direction move_direction);
    string left(int maximum_number_of_cells) const;
    string right(int maximum_number_of_cells) const;
    char current_character() const;
};
#endif
