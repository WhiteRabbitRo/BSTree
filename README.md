[![Build Status](https://travis-ci.org/WhiteRabbitRo/BSTree.svg?branch=master)](https://travis-ci.org/WhiteRabbitRo/BSTree)

# BSTree
C++ Project "Binary Search Tree"

**General information**

Your attention is represented by the implementation of a binary search tree in the programming language C++. The following functions are implemented in this assembly (a.k.a class methods) for working with BSTree: 

- displaying the tree on the screen
- displaying the list of tree nodes (3 ways)
- adding a node to the tree
- removing the node from the tree 
- saving the tree to the file
- loading the tree from the file
- checking for a node

Also implemented are methods such as an initialization list and two statements: output to the stream and an assignment operator.

## How to build the project

**To run the MAIN-file**

```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
$ cd _build
$ ./bstree <item1> <item2> <item3> ...
```

The program supports the ability to run with the input data specified (a space character is used as a separator), and also without input data.

**To run the examples**

```ShellSession
$ cmake -H. -B_build -DBUILD_EXAMPLES=ON
$ cmake --build _build
$ cd _build
$ ./example
```

**To run the tests**

```ShellSession
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build --target install
$ cmake --build _build --target test -- ARGS=--verbose
```
