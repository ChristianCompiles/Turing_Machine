// Module: Main
// File: Main.cpp
// Application: Turing Machine
// Computer: MSI GS65 9SD Stealth
// Operating System: Ubuntu 22.04.4 LTS
// Course: CPT_S 322 Software Design I
// Author: Christian L. Penick
// Date: 04/24/2024

// Description
// Main.cpp validates command lines arguments, intializes Turing Machine,
// validates user commands, and sends messages to the TM to perform commands

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Turing_Machine.h"
#include "TM_Utils.h"
using std::string;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::invalid_argument;
using std::exception;

// Name: handle_user_command
// Purpose: takes a user command and if it's a valid command,
//          performs the appropriate command, either through
//          messages to the Turing Machine object, or using
//          other data structures in main.
int handle_user_command(char cmd_char, Turing_Machine& TM,
                        vector<string>& input_strings, bool& str_list_modified,
                        const string& input_file_name, int& num_transition_per_run,
                        int& num_cells_in_id)
{
    cmd_char = (char)toupper(cmd_char);
    string raw_CL_input;

    if (cmd_char == 'D') // delete
    {
        cout << "Enter number of line to delete: ";
        getline(cin, raw_CL_input);

        int user_num = parse_string_to_int(raw_CL_input);

        if(user_num == 0)
            return 0;

        if(user_num - 1 < input_strings.size())
        {
            str_list_modified = true;
            input_strings.erase((input_strings.begin() + (user_num-1)));
        }
        else
            cout << "Invalid line to delete.\n";

        return 0;
    }
    else if (cmd_char == 'X') // exit
    {
        if(str_list_modified) // write to file
        {
            ofstream writeInputStringFile(input_file_name, std::ios::trunc);

            if(writeInputStringFile.is_open())
            {
                int num_strings = (int)input_strings.size();
                int count = 0;

                for(const auto& i : input_strings)
                {
                    if(i.empty())
                        writeInputStringFile << '\\';
                    else
                        writeInputStringFile << i;
                    if(count < num_strings -1)
                        writeInputStringFile << endl;
                    ++count;
                }
                cout << "Input string file written successfully.\n";
            }
            else
            {
                cout << "Could not write input string file successfully\n";
            }
        }

        return 1; // return one will signal in main to exit program
    }
    else if (cmd_char == 'H') // help
    {
        cout << "Delete (D): Delete input string from list\n";
        cout << "Exit (X): Exit application\n";
        cout << "Help (H): Help user\n";
        cout << "Insert (I): Insert input strings into list\n";
        cout << "List (L): List input strings\n";
        cout << "Quit (Q): Quit operation of Turing machine on input string\n";
        cout << "Run (R): Run Turing Machine on input string\n";
        cout << "Set (E): Set maximum number of transitions to perform\n";
        cout << "Show (W): Show status of application\n";
        cout << "Truncate (T): Truncate instantaneous descriptions\n";
        cout << "View (V): View Turing Machine\n";
        return 0;
    }
    else if(cmd_char == 'I') // insert
    {
        cout << "New input string: ";
        getline(cin, raw_CL_input);

        if(!raw_CL_input.empty())
        {
            if(raw_CL_input.length() == 1 && raw_CL_input[0] == '\\')
                raw_CL_input = ""; // empty string

            if(TM.is_valid_input_string(raw_CL_input) && (std::count(input_strings.begin(), input_strings.end(), raw_CL_input) == 0))
            {
                str_list_modified = true;
                input_strings.push_back(raw_CL_input);
            }
        }
        return 0;
    }
    else if(cmd_char == 'L') // list input strings
    {
        cout << endl;
        cout << "Input strings:\n";

        if(input_strings.empty())
        {
            cout << "Empty.\n";
            return 0;
        }

        int num = 1;
        for(const auto& i : input_strings)
        {
            cout << num << ") ";
            if(i.empty()) // empty string
                cout << "\\";
            else
                cout << i;
            cout << endl;
            ++num;
        }
        return 0;
    }
    else if (cmd_char == 'Q') // quit
    {
        if(TM.is_operating())
        {
            TM.terminate_operation();
            cout << "Input string: " << TM.input_string() << endl;
            cout << "Total number of transitions performed: " << TM.total_number_of_transitions() << endl;
            cout << "Input string is neither accepted nor rejected.\n";
        }
        else
            cout << "Turing Machine not running on input string.\n";

        return 0;
    }
    else if (cmd_char == 'R') // run
    {
        if(!TM.is_valid_definition())
        {
            cout << "Cannot operate invalid Turing Machine.\n";
            return 0;
        }

        if(!TM.is_operating()) // if not operating
        {
            cout << endl;
            cout << "Enter line of input string to run: ";
            getline(cin, raw_CL_input);

            if(raw_CL_input.empty())
                return 0;

            int user_num = parse_string_to_int(raw_CL_input);

            if(user_num == 0)
                return 0;

            if(user_num - 1 >= input_strings.size())
            {
                cout << "Not valid choice from input string list.\n";
                return 0;
            }

            TM.initialize(input_strings.at(user_num-1));
            TM.view_instantaneous_descriptions(num_cells_in_id);
        }

        try
        {
            TM.perform_transitions(num_transition_per_run);
        }
        catch(Crash& ec)
        {
            cout << red_start << ec.what() << color_reset;
        }

        TM.view_instantaneous_descriptions(num_cells_in_id);

        if(TM.is_accepted_input_string() || TM.is_rejected_input_string())
        {
            cout << endl;
            cout << "Total number of transitions performed: " << TM.total_number_of_transitions() << endl;
            cout << "Original input string: ";
            if(TM.input_string().empty())
                cout << "\\" << endl;
            else
                cout << TM.input_string() << endl;
        }

        if(TM.is_accepted_input_string())
        {
            cout << "Accepted.\n";
        }
        else if (TM.is_rejected_input_string())
        {
            cout << "Rejected.\n";
        }

        return 0;
    }
    else if (cmd_char == 'E') // set
    {
        // set 
        cout << "Maximum number of transitions[" << num_transition_per_run << "]: ";
        getline(cin, raw_CL_input);

        int user_num = parse_string_to_int(raw_CL_input);

        if(user_num > 0)
        {
            num_transition_per_run = user_num;
            cout << "Setting changed.\n";
        }

        return 0;
    }
    else if(cmd_char == 'W') // show
    {
        // accounting info
        cout << "CPTS 322\nSpring 2024\nDr. Corrigan\nChristian Penick\nVersion: Final Submission\n";
        // default settings
        cout << "Max number of transition to perform at a time: " << num_transition_per_run << endl;
        cout << "Max number of cells to left and right of tape head to display in ID: " << num_cells_in_id << endl;
        // name of TM
        cout << "Name of Turing Machine: " << input_file_name.substr(0, input_file_name.length()-4) << endl;

        // status of TM
        if(!TM.is_used())
            cout << "Not used.\n";
        else if(TM.is_operating())
            cout << "Running.\nInput string: " << TM.input_string() << endl << "Transitions performed: " << TM.total_number_of_transitions() << endl;
        else // TM ran on string
        {
            cout << "Last input string: " << TM.input_string() << endl << "Transitions performed: " << TM.total_number_of_transitions() << endl;
            if(TM.is_accepted_input_string())
                cout << "Accepted.\n";
            else if(TM.is_rejected_input_string())
                cout << "Rejected.\n";
            else
                cout << "Quit before determination of acceptance/rejection.\n";
        }

        if(str_list_modified)
            cout << "List of input strings will be written to " << input_file_name << endl;

        return 0;
    }
    else if(cmd_char == 'T') // truncate
    {
        // truncate amount shown on ID
        cout << "Number of cells[" << num_cells_in_id << "]: ";
        getline(cin, raw_CL_input);

        int user_num = parse_string_to_int(raw_CL_input);

        if(user_num != 0)
        {
            num_cells_in_id = user_num;
            cout << "Setting changed.\n";
        }

        return 0;
    }
    else if (cmd_char == 'V') // view
    {
        TM.view_definition();
        return 0;
    }
    else
    {
        cout << "Invalid command.\n";
        return 0; // return 0 if invalid cmd given
    }
}

// Name: load_input_strings
// Purpose: read in newline delimited input strings from the input string file
vector<string> load_input_strings(const string& input_string_file_name,
                                  const Turing_Machine& tm,
                                  bool& str_list_modified)
{
    vector<string> vector_of_input_strings;

    ifstream readFile;
    readFile.open(input_string_file_name);

    if(!readFile.is_open())
    {
        return vector_of_input_strings;
    }

    string value;

    while(getline(readFile, value))
    {
        if(value.length() == 1 && value[0] == '\\')
            value = ""; // empty string

        if(value.back() == '\n') // remove newline if exists in string
            value.pop_back();

        if(count(vector_of_input_strings.begin(), vector_of_input_strings.end(), value) == 0) // check if dup
        {
            if(tm.is_valid_input_string(value)) // if input string solely composed of input alphabet
                vector_of_input_strings.push_back(value);
            else
                str_list_modified = true;
        }
        else
            str_list_modified = true;
    }

    readFile.close();

    return vector_of_input_strings;
}

// Name: main
// Purpose: validates command lines arguments,
//          intializes Turing Machine,
//          performs command loop control
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Incorrect program invocation: ./progname TM_def_file\n\n";
        return 0;
    }

    // define config settings
    int num_transition_per_run = 1;
    int num_cells_in_id = 32;

    string definition_file_name = string(argv[1]) + ".def";
    string input_string_file_name = string(argv[1]) + ".str";

    Turing_Machine tm(definition_file_name);
   
    bool str_list_modified = false;
    vector<string> input_strings = load_input_strings(input_string_file_name, tm, str_list_modified); // load input strings

    string user_input;
    int cmd_flag = 0;

    cout << "Loaded!\n";

    while (cmd_flag != 1)
    {
        cout << "\nCommand: ";
        getline(cin, user_input);

        if(user_input.empty())
            continue;

        if(user_input.length() != 1) // more than char and newline, so skip user input
        {
            cout << "Invalid input.\n";
            continue;
        }
        cmd_flag = handle_user_command(user_input[0], tm, input_strings, str_list_modified, input_string_file_name, num_transition_per_run, num_cells_in_id);
    }
    return 0;
}
