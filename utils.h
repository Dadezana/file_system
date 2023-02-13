#ifndef UTILS_H
#define UTILS_H

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "trie.h"
#include "colors.h"
using std::string;
using std::cout;

int getch(){
   struct termios oldattr, newattr;
   int ch;
   tcgetattr(0, &oldattr);
   newattr=oldattr;
   newattr.c_lflag &= ~( ICANON | ECHO );
   tcsetattr( 0, TCSANOW, &newattr);
   ch=getchar();
   tcsetattr(0, TCSANOW, &oldattr);
   return(ch);
}

string get_command(Trie* trie){
    char ch = 'a';
    string command="", completed_word;
    Char* ptr = trie->_root;

    while(ch != '\n')
    {
        ch = getch();

        if(ch == '\n'){
            cout << "\n";
            return command;
        }
        else if(ch == '\t')
        {
            // cout << "\n";
            ptr = trie->search(trie->_root, command);

            if(ptr == nullptr) continue;

            if(ptr->children.size() <= 1)
            {
                command += completed_word;
                cout << "\r> " << command;
                continue;
            }

            trie->display_all_completitions(ptr, command);
            cout << "\n> " << command;
            continue;
        }

        command += ch;
        cout << "                ";
        cout << "\r> " << command;
        ptr = trie->search(trie->_root, command);
        completed_word = trie->get_completition(ptr);
        cout << GREEN << completed_word << RESET;
    }

    return command;

}

#endif