// Module: Transition
// File: Transition.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Transition.cpp implements the methods of the class Transition

#include "Transition.h"

// Name: Transition
// Purpose: This constructor intializes all the member
//          variables of the class Transition to create an
//          object of said class.
Transition::Transition(string source_state, char read_character,
        string destination_state, char write_character,
        Direction direction) : source(source_state), read(read_character), destination(destination_state),
                               write(write_character), move(direction){}


// Name: source_state
// Purpose: returns member variable: source
string Transition::source_state() const {return source;}

// Name: read_character
// Purpose: returns member variable: read_character
char Transition::read_character() const {return read;}

// Name: destination_state
// Purpose: returns member variable: destination
string Transition::destination_state() const {return destination;}

// Name: write_character
// Purpose: returns member variable: write
char Transition::write_character() const {return write;}

// Name: move_direction
// Purpose: returns member variable: move
Direction Transition::move_direction() const {return move;}
