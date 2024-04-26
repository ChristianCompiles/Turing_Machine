// Module: Input_Alphabet
// File: Input_Alphabet.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Input_Alphabet.h provides the private members and public declarations
// for the class Input_Alphabet

#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Tape_Alphabet.h"
using std::vector;
using std::ifstream;
using std::cout;
using std::string;
using std::endl;

class Input_Alphabet
{
private:
    vector<char> alphabet = {};
public:
    void load(ifstream& definition, bool& valid);
    void validate(const Tape_Alphabet& tape_alphabet, bool& valid);
    void view();
    bool is_element(char value) const;
};
#endif