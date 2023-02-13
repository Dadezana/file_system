#include "shell.h"


Shell::Shell(){

    path = "/";
    cmds.insert({"exit", 0});
    cmds.insert({"touch", 1});
    cmds.insert({"mkdir", 2});
    cmds.insert({"ls", 3});
    cmds.insert({"cd", 4});
    cmds.insert({"find", 5});
    cmds.insert({"cls", 6});
    cmds.insert({"rm", 7});
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

    if(pos == NOT_FOUND){
        command = cmd;
        return;
    }

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

    if(cmds.find(command) != cmds.end()){
        return cmds[command];
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
