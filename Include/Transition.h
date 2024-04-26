// Module: Transition
// File: Transition.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Transition.h provides the private members and public declarations
// for the class Transition

#ifndef TRANSITION_H
#define TRANSITION_H
#include <string>
#include "TM_Utils.h"
using std::string;

class Transition
{
private:
    const string source;
    const char read;
    const string destination;
    const char write;
    const Direction move;

public:
    Transition(string source_state, char read_character,
                    string destination_state, char write_character,
                    Direction direction);
    string source_state() const;
    char read_character() const;
    string destination_state() const;
    char write_character() const;
    Direction move_direction() const;
};
#endif
