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

    public:
        string path = "/";

        Node* root;
        Trie() : root(new Node("/", true)) {};
        
        void create_folder(string name, Node* pos);
        void create_file(string name, Node* pos);
        
        void search(Node* pos, string name, string path="");    // if path is empy the root is taken
        void display(Node* pos);
        
        Node* move(Node* cur_pos, string name, Shell* shell);
};

#endif