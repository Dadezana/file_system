/*
    This program is supposed to act like a simplified version of the file system
*/

#include "trie.h"
#include "shell.h"
#include "utils.h"


int main(){

    // const int CREATE_FILE = 1;
    // const int CREATE_FOLDER = 2;
    // const int LIST_DIR = 3;
    // const int CHANGE_DIR = 4;
    // const int SEARCH = 5;
    // const int CLS = 6;

    Trie file_system;
    Shell shell;

    Node* cur_pos = file_system.root;
    int choice = -1;
    string name = "";

    vector<string>::iterator it;

    do{
        shell.type_prompt();
        // split command
        shell.split_arguments( get_command(&file_system) );

        switch(shell.get_command()){

            case EXIT_SUCCESS:
                exit(0);
                break;

            case Shell::CREATE_FILE:
                
                it = shell.get_next_argument();
                if(it == shell.get_args_end()) break;

                do
                {
                    if(it == shell.get_args_end()) break;
                    
                    name = *it;
                    file_system.mkdir(name, cur_pos, true);
                    it++;

                }while((it = shell.get_next_argument(it)) != shell.get_args_end());
                break;

            case Shell::CREATE_FOLDER:

                it = shell.get_next_argument();
                if(it == shell.get_args_end()) break;

                do
                {
                    name = *it;
                    file_system.mkdir(name, cur_pos);
                    it++;

                }while((it = shell.get_next_argument(it)) != shell.get_args_end());
                break;

            case Shell::LIST_DIR:
                file_system.display(cur_pos);
                break;

            case Shell::CHANGE_DIR:

                it = shell.get_next_argument();
                if(it == shell.get_args_end()) break;

                do
                {

                    name = *it;
                    cur_pos = file_system.change_directory(cur_pos, name, &shell);
                    it++;

                }while((it = shell.get_next_argument(it)) != shell.get_args_end());
                break;

            case Shell::SEARCH:
                
                it = shell.get_next_argument();
                if(it == shell.get_args_end()) break;
                do
                {
                    
                    name = *it;
                    file_system.find(file_system.root, name);
                    it++;

                }while( (it = shell.get_next_argument(it)) != shell.get_args_end() );
                break;

            case Shell::CLS:
                system("cls");
                break;

            case Shell::RM:
                it = shell.get_next_argument();
                if(it == shell.get_args_end()) break;
                do
                {
                    
                    name = *it;
                    file_system.rm(cur_pos, name);
                    it++;

                }while( (it = shell.get_next_argument(it)) != shell.get_args_end() );
                break;

            case Shell::EMPTY_INPUT:
                break;

            default:
                shell.command_not_found();
                break;

        }

    }while(choice != EXIT_SUCCESS);

    return 0;
}