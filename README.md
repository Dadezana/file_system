# Shell and file system simulator<br>![Linux](https://img.shields.io/badge/platform-linux-brightgreen?style=for-the-badge&logo=linux) ![Language](https://img.shields.io/badge/language-C++-red?style=for-the-badge&logo=cplusplus)<br>
I made this program to practice with tree data structure.<br>
It's a shell like enviroment where you can manage folders, subfolders and files.<br>
I also implemented an auto-completition system in real time. To complete a word just press 'tab' key.
# Commands
### Create a folder.
```bash
mkdir <folder_name>
```
### Create a file
```bash
touch <file_name>
```
### Remove a folder/file
```bash
rm <folder_name>
```
### List dir content
```bash
ls
```
### Move into a directory
```bash
cd <folder_name>
```
### Clear terminal screen
```bash
cls
```
### Search for file/folders across all file system
```bash
find <name>
```

# How to build
```bash
g++ *.cpp
```

# Todo

- [X] Auto-complete feature 
- [X] Erase a char when pressing the backspace key
- [ ] List directory  indicated by the path and not just the current one *(`ls` command)*
- [ ] Add content to file *(write text into it)*