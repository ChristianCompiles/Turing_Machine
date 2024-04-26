// Module: States
// File: States.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// States.h provides the private members and public declarations
// for the class States

#ifndef STATES_H
#define STATES_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using std::string;
using std::vector;
using std::cout;
using std::ifstream;
using std::endl;

class States
{
private:
    vector<string> names = {};
public:
    void load(ifstream& definition, bool& valid);
    void view();
    bool is_element(const string& value) const;
};
#endif
