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

```ShellSession
$ cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=install
$ cmake --build _build --target install
```

**To run the MAIN-file**

```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
$ cd _build
$ ./main <item1> <item2> <item3> ...
```

The program supports the ability to run with the input data specified (a space character is used as a separator), and also without input data.

**To run the examples**

```ShellSession
$ cmake -H. -B_build -DBUILD_EXAMPLES=ON
$ cmake --build _build --target install
$ cd _build
$ ./example
```

**To run the tests**

```ShellSession
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build --target install
$ cmake --build _build --target test -- ARGS=--verbose
```

## Benchmark

The bencmark for 10 ^ (1 : 9) elements (all values in seconds):
|Amount of elements|Adding|
|10^1|2.8e-05|
|10^2|4e-05|
|10^3|0.000458|
|10^4|0.005158|
|10^5|0.08702|
|10^6|1.51488|
|10^7|24.2715|
|10^8|353.768|
|10^9|4981.37|
