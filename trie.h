#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <string>
#include "colors.h"
#include "shell.h"
using namespace std;

struct Node{
    string name;
    bool is_folder;
    vector<Node*> children;
    Node(string d, bool folder) : name(d), is_folder(folder) {}
    Node* parent;

    bool is_end_of_name = false;
};

struct Char{
    char c;
    bool is_end_of_name = false;
    vector<Char*> children;
    Char(char c) : c(c) {}
};

class Trie{

    private:
        vector<string> path_component;
        void split_component(string path);
        
        Node* change_dir(Node* cur_pos, string name, Shell* shell=nullptr);

        void create_folder(string name, Node* pos);
        void create_file(string name, Node* pos);

    public:
        string path = "/";  // path the user is currently in

        Node* root;     // Directory structure
        Char* _root;    // All shell commands
        // Trie() : root(new Node("/", true)) {};
        Trie();
        
        void mkdir(string name, Node* pos, bool want_to_create_file=false);
        void rm(Node* pos, string name="");
        
        void find(Node* pos, string name, string path="");    // if path is empy the root is taken
        void display(Node* pos);
        
        Node* change_directory(Node* cur_pos, string path, Shell* shell=nullptr);

        // used for auto completition
        Char* search(Char* node, string word);
        string get_completition(Char* node, string word="");
        void display_all_completitions(Char* node, string word="");
        void insert_command(string name);
};

#endif