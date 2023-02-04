#include "trie.h"


void Trie::create_file(string name, Node* pos)
{
    if(name == "") return;
    Node* newNode = new Node(name, false);
    newNode->parent = pos;
    pos->children.push_back(newNode);
}

void Trie::create_folder(string name, Node* pos)
{
    if(name == "") return;
    Node* newNode = new Node(name, true);
    newNode->parent = pos;
    pos->children.push_back(newNode);
}

// Search for a file across all file system
void Trie::search(Node* pos, string name, string path){

    if(pos == nullptr) return;
    if(pos->children.empty()) return;     // leaf node, so no other node needs to be checked

    for(Node* child : pos->children)
    {
        if(child->name.compare(name) == 0)
        {
            cout << "\n" << path << "/" << name;

            if(child->is_folder) 
                cout << "/";
        }

        search(child, name, path+"/"+child->name);
    }
}

// Display files in current position
void Trie::display(Node* cur_pos){

    if(cur_pos == nullptr) return;

    for(Node* child : cur_pos->children){

        if(child->is_folder) cout << BOLDGREEN;
        else cout << BOLDWHITE;

        cout << child->name << "\n";
    }
    cout << RESET;
}

// Move into the specified folder
Node* Trie::move(Node* cur_pos, string folder, Shell* shell){
    
    if(cur_pos == nullptr) return cur_pos;

    // if '..' is typed move to the parent directory
    if(folder.compare("..") == 0){
        if(cur_pos->name == "/") return cur_pos;
        path = path.substr(0, path.size() - 1);         // remove the last char "/"
        path = path.substr(0, path.find_last_of("/"));  // remove the current folder from the path
        path += "/";                                    // re-add the final "/"
        shell->set_path(this->path);
        return cur_pos->parent;
    }

    // otherwise check if the folder exists and move into it
    for(Node* child : cur_pos->children){
        if(child->name.compare(folder) == 0)
        {
            if(!child->is_folder)
            {
                cout << RED << "\"" << folder << "\" is a file. Cannot move into it.\n" << RESET;
                return cur_pos;
            }
            cur_pos = child;
            path += cur_pos->name + "/";
            shell->set_path(this->path);  
            return cur_pos;
        }
    }

    cout << RED << "\"" << folder << "\" does not exists\n" << RESET;
    return cur_pos;
}