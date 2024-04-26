cmake_minimum_required(VERSION 3.22)

project(TM_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        Src/Tape.cpp
        Src/Transition_Function.cpp
        Src/Final_States.cpp
        Src/Input_Alphabet.cpp
        Src/Main.cpp
        Src/States.cpp
        Src/Tape_Alphabet.cpp
        Src/Turing_Machine.cpp
        Src/Transition.cpp
        Src/Crash.cpp
        Src/TM_Utils.cpp)

add_executable(TM_app ${SOURCES})

target_include_directories(TM_app PRIVATE Include)
