#include "shell.h"


Shell::Shell(){
    path = "/";
}

// Split the command given. Assigns the command to `command` variable, and all the arguments to the `args` vector
// @param cmd command entered in prompt
void Shell::split_arguments(string cmd){
    
    args.clear();   // no need to keep old argument if new command is given

    if(cmd.empty()){
        command = cmd;
        return;
    }

    string token = "";
    size_t pos;
    // take the command
    pos = cmd.find(" ");

    if(pos == NOT_FOUND)
        return;

    command = cmd.substr(0, pos);
    cmd = cmd.substr(++pos);


    // find the arguments
    while (true)
    {
        pos = cmd.find(" ");
        if(pos == NOT_FOUND)            // if there are no more spaces 
        {
            if(cmd.empty()) return;     // and the string is no empty

            args.push_back(cmd);        // it means it's an argument
            return;
        }
            
        

        token = cmd.substr(0, pos);
        cmd = cmd.substr(++pos);

        args.push_back(token);
    }
    

}

vector<string>::iterator  Shell::get_next_argument(vector<string>::iterator it){

    if(it == vector<string>::iterator()){
        return args.begin();
    }

    if(it == args.end()) return args.end();

    return it;

}
// @return The command given. -1 if command not found.
int Shell::get_command() { 

    if(command.empty()){
        return EMPTY_INPUT;
    }

    if(command.compare("exit") == 0){
        return 0;
    }
    else if(command.compare("touch") == 0){
        return 1;
    }
    else if(command.compare("mkdir") == 0){
        return 2;
    }
    else if(command.compare("ls") == 0){
        return 3;
    }
    else if(command.compare("cd") == 0){
        return 4;
    }
    else if(command.compare("find") == 0){
        return 5;
    }
    else if (command.compare("cls") == 0){
        return 6;
    }

    return -1; 
}

vector<string>::iterator Shell::get_args_end() { 
    return args.end();
}

// inline void Shell::type_prompt(string prompt){
//     cout << path << "\n";
//     cout << prompt;
// }

void Shell::set_path(string path)
{
    this->path = path;
}

void Shell::wait_for_command(){
    getline(cin, command);
    split_arguments(command);
}