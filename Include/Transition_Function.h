// Module: Transition_Function
// File: Transition_Function.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Transition_Function.h provides the private members and public declarations
// for the class Transition_Function.

#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Tape_Alphabet.h"
#include "States.h"
#include "Final_States.h"
#include "TM_Utils.h"
#include "Transition.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Transition_Function
{
private:
    vector<Transition> transitions = {};

public:
    void load(ifstream& definition, bool& valid);
    void validate(const Tape_Alphabet& tape_alphabet, const States& states,
                  const Final_States& final_states, bool& valid) const;
    void view() const;
    void find_transition(const string& source_state, char read_character,
                         string& destination_state, char& write_character,
                         Direction& move_direction, bool& found) const;
};
#endif
