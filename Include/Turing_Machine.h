// Module: Turing_Machine
// File: Turing_Machine.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Turing_Machine.h provides the private members and public declarations
// for the class Turing_Machine

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include <vector>
#include "Tape.h"
#include "Input_Alphabet.h"
#include "Tape_Alphabet.h"
#include "Transition_Function.h"
#include "States.h"
#include "Final_States.h"
using std::string;
using std::vector;
class Turing_Machine
{
private:
    vector<string> description;
    string initial_state;
    string current_state;
    string original_input_string;
    int number_of_transitions = 0;
    bool valid;
    bool used;
    bool operating;
    bool accepted;
    bool rejected;

    Tape tape;
    Input_Alphabet input_alphabet;
    Tape_Alphabet tape_alphabet;
    Transition_Function transition_function;
    States states;
    Final_States final_states;
    ifstream definition;
public:
    explicit Turing_Machine(const string& definition_file_name);
    void view_definition();
    void view_instantaneous_descriptions(int maximum_number_of_cells);
    void initialize(const string& input_string);
    void perform_transitions(int maximum_number_of_transitions);
    void terminate_operation();
    string input_string();
    int total_number_of_transitions() const;
    bool is_valid_definition() const;
    bool is_valid_input_string(const string& value) const;
    bool is_used() const;
    bool is_operating() const;
    bool is_accepted_input_string() const;
    bool is_rejected_input_string() const;
};
#endif
