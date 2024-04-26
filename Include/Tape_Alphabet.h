// Module: Tape_Alphabet
// File: Tape_Alphabet.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Tape_Alphabet.h provides the private members and public declarations
// for the class Tape_Alphabet

#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H
#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using std::ifstream;
using std::cout;

class Tape_Alphabet
{
private:
    vector<char> alphabet = {};
public:
    void load(ifstream& definition, bool& valid);
    void view();
    bool is_element(char value) const;
};
#endif
