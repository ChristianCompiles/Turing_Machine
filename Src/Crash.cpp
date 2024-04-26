// Module: Crash
// File: Crash.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Crash.cpp implements the constructor for class Crash

#include "Crash.h"
#include <stdexcept>

// constructor takes string and initializes runtime_error with it
Crash::Crash(const string& reason) : runtime_error(reason.c_str()){}
