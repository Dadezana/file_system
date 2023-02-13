#include "trie.h"

Trie::Trie(){
    _root = new Char('/');
    insert_command("exit");
    insert_command("touch");
    insert_command("mkdir");
    insert_command("ls");
    insert_command("cd");
    insert_command("find");
    insert_command("cls");
    insert_command("rm");

    root = new Node("/", true);
}

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


void Trie::mkdir(string name, Node* pos, bool want_to_create_file)
{
    if(name.empty()) return;

    string folder = name;
    split_component(name);
    
    // if a path is specified instead of the folder name only
    if(path_component.size() > 1)
    {
        
        folder = path_component.back();     // get the folder name
        path_component.pop_back();          // and remove it from the vector

        for(string dir : path_component){
            pos = change_dir(pos, dir);
        }
    }
    
    if(want_to_create_file) 
        create_file(folder, pos);
    else 
        create_folder(folder, pos);
}


// Search for a file across all file system
void Trie::find(Node* pos, string name, string path){

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

        find(child, name, path+"/"+child->name);
    }
}

// delete a folder. The name needs to be specified only during the first call
void Trie::rm(Node* pos, string name){
    
    if(pos == nullptr) return;

    string folder = name;
    split_component(name);
    
    // if a path is specified instead of the folder name only
    if(path_component.size() > 1)
    {
        
        folder = path_component.back();     // get the folder name
        path_component.pop_back();          // and remove it from the vector

        for(string dir : path_component){
            pos = change_dir(pos, dir);
        }
    }
    
    vector<Node*>::iterator it = pos->children.begin();

    if(!folder.empty())
    {
        while(it != pos->children.end())
        {
            if((*it)->name == folder)
            {
                pos->children.erase(it);
                break;
            }
            it++;
        }
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
Node* Trie::change_dir(Node* cur_pos, string folder, Shell* shell){
    
    if(cur_pos == nullptr) return cur_pos;

    bool restore_path = (shell == nullptr);   // useful to know wether we are moving just to create a file/folder or the user used 'cd' command

    // if '..' is typed move to the parent directory
    if(folder.compare("..") == 0){
        if(cur_pos->name == "/") return cur_pos;
        if(!restore_path)
        {
            path = path.substr(0, path.size() - 1);             // remove the last char "/"
            path = path.substr(0, path.find_last_of("/"));      // remove the current folder from the path
            path += "/";                                        // re-add the final "/"
            shell->set_path(this->path);
        }
                                         
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
            if(!restore_path)
            {
                path += cur_pos->name + "/";
                shell->set_path(this->path);  
            }
            return cur_pos;
        }
    }

    cout << RED << "\"" << folder << "\" does not exists\n" << RESET;
    return cur_pos;
}

/**
    Take the path given ("/folder1/folder2/"), remove the "/" and store every single folder name into the 'path_component' vector.
    Then it calls, as many times as the folders in path_component, the change_dir() function to effectively change the directory.
    @param path path to split 
*/
Node* Trie::change_directory(Node* cur_pos, string path, Shell* shell)
{
    if(path.empty()) return cur_pos;

    if(path.find("/") == Shell::NOT_FOUND)
        return change_dir(cur_pos, path, shell);

    split_component(path);

    for(string folder : path_component){
        cur_pos = change_dir(cur_pos, folder, shell);
    }

    return cur_pos;

}


// Split the path into subfolders and save the result in path_component vector
void Trie::split_component(string path){

    path_component.clear();

    char first_char = path[0];
    if(first_char == '/'){
        path = path.substr(1);                  // remove the first "/"
    }

    char last_char = path.back();
    if(last_char == '/'){
        path = path.substr(0, path.size()-1);   // remove the last "/"
    }

    size_t pos;
    string token = "";
    // find the arguments
    while (!path.empty())
    {
        pos = path.find("/");
        if(pos == Shell::NOT_FOUND)            // if there are no more slashes 
        {
            if(path.empty()) break;            // and the string is no empty

            path_component.push_back(path);        // it means it's an argument
            break;
        }    
        
        token = path.substr(0, pos);
        path = path.substr(++pos);

        path_component.push_back(token);
    }
}


//* AUTO-COMPLETITION


/// @brief Search for a word inside the trie 
/// @return A pointer to the end of the word searched
Char* Trie::search(Char* node, string word)
{
    if(node == nullptr) return node;

    char ch = word[0];

    for(Char* child : node->children)
    {
        if(ch == child->c)                      // if the char is equal.
        {
            if(word.length() <= 1)              // and the lenght is 1
                return child;                   // means we found every char
            else 
                return search(child, word.substr(1));     // otherwise keep searching for other chars
        }
    }
    
    return nullptr;
}


string Trie::get_completition(Char* node, string word)
{
    if(node == nullptr) return word;
    if(node->children.size() == 0) return word;
    srand(time(NULL));

    int n = rand() % node->children.size();

    Char* child = node->children.at(n);

    word += child->c;

    if(child->is_end_of_name)
    {
        // cout << GREY << word << RESET;
        return word;
    }

    return get_completition(child, word);

}


void Trie::display_all_completitions(Char* node, string word){
    
    if(node == nullptr) return;

    if(node->is_end_of_name){
        cout << GREEN << word << RESET << endl;
    }

    for(Char* child : node->children){
        char c = child->c;
        display_all_completitions(child, word + c);     // iterate through the children of this node (child)
    }
}

void Trie::insert_command(string name){
    if(name == "") return;
    Char* current = _root;

    for (char ch : name)                        //* for every char
    {
        bool chExists = false;
    
        for(Char* child : current->children)
        {
            if(child->c == ch){                 //* check if that char already exists
                chExists = true;            
                current = child;                //* if yes move to that node
                break;
            }
        }

        if(!chExists){                          //* if not, create a new node and move to it
            Char* newNode = new Char(ch);
            current->children.push_back(newNode);
            current = newNode;
        }
    }
    current->is_end_of_name = true;
}