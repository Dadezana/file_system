#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include "colors.h"
#include <vector>
#include <map>
using namespace std;


class Shell{

    const std::streamsize MAX_CMD_LEN = 50;
    string command;
    vector<string> args;
    string path;

    map<string, int> cmds;

    public:
        static const size_t NOT_FOUND = string::npos;
        static const int CREATE_FILE = 1;
        static const int CREATE_FOLDER = 2;
        static const int LIST_DIR = 3;
        static const int CHANGE_DIR = 4;
        static const int SEARCH = 5;
        static const int CLS = 6;
        static const int RM = 7;
        static const int EMPTY_INPUT = -2;

        Shell();

        // void wait_for_command();
        void split_arguments(string args);

        inline void command_not_found(){
            cout << RED << "\"" << command << "\" command not found\n" << RESET;
        }

        void set_path(string path);
        
        int get_command();
        vector<string>::iterator get_args_end();
        vector<string>::iterator get_next_argument(vector<string>::iterator it = vector<string>::iterator());         //! every time it's called it returns the next argument (1 string for call)
        
        inline void type_prompt(string prompt="> "){
            cout << BOLDYELLOW << "\n" << path << "\n" << RESET;
            cout << prompt;
        }
};

#endif