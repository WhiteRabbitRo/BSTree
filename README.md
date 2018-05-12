# BSTree
C++ Project "Binary Search Tree"

# General information
Your attention is represented by the implementation of a binary search tree in the programming language C++. The following functions are implemented in this assembly (a.k.a class methods) for working with BSTree: 

- displaying the tree on the screen
- displaying the list of tree nodes (3 ways)
- adding a node to the tree
- removing the node from the tree 
- saving the tree to the file
- loading the tree from the file
- checking for a node

Also implemented are methods such as an initialization list and two statements: output to the stream and an assignment operator.

# How to compile the program
You can compile the program through the command line of the terminal:

To compile MAIN file use:
$ g++ -I./include -std=c++14 -c sources/main.cpp
$ g++ main.o

To compile EXAMPLE file use:
$ g++ -I./include -I./sources/bstree.cpp -std=c++14 -c examples/example.cpp
$ g++ example.o

Or with the help of built-in IDE-environment compilers.

# How to run the program
The format of running the program through the command line is as follows:

$ ./bstree <<item1>> <<item2>> <<item3>> ...

The program supports the ability to run with the input data specified (a space character is used as a separator), and also without input data.
