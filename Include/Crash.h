// Module: Crash
// File: Crash.h
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Crash.h provides the public declarations
// for the class Crash

#ifndef CRASH_H
#define CRASH_H

#include <stdexcept>
#include <string>
using std::string;
using std::runtime_error;

class Crash : public runtime_error
{
public:
    Crash(const string& reason);
};
#endif
