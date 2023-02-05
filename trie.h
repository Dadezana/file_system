#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <string>
#include "utils.h"
#include "shell.h"
using namespace std;

struct Node{
    string name;
    bool is_folder;
    vector<Node*> children;
    Node(string d, bool folder) : name(d), is_folder(folder) {}
    Node* parent;
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

        Node* root;
        Trie() : root(new Node("/", true)) {};
        
        void mkdir(string name, Node* pos, bool want_to_create_file=false);
        void rm(Node* pos, string name="");
        
        void search(Node* pos, string name, string path="");    // if path is empy the root is taken
        void display(Node* pos);
        
        Node* change_directory(Node* cur_pos, string path, Shell* shell=nullptr);
};

#endif