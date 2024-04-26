// Module: Final_States
// File: Final_States.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Final_States.h provides the private members and public declarations
// for the class Final_States

#ifndef FINAL_STATES_H
#define FINAL_STATES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "States.h"
using std::string;
using std::vector;
using std::ifstream;
using std::cout;

class Final_States {
private:
    vector<string> names = {};
public:
    void load(ifstream& definition, bool &valid);

    void validate(const States& states, bool &valid);

    void view();

    bool is_element(const string &value) const;
};
#endif