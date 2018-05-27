[![Build Status](https://travis-ci.org/WhiteRabbitRo/BSTree.svg?branch=master)](https://travis-ci.org/WhiteRabbitRo/BSTree)

https://whiterabbitro.github.io/BSTree/index.html

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


|Amount of elements|Adding|Existing|Print|Direct print|Symmetric print|Reverse print|Saving|Loading|Removing|
|---|---|---|---|---|---|---|---|---|---|
|10^1|3.1e-05|3e-06|0.000101|6e-06|5e-06|6e-06|0.000295|0.000178|4e-06|
|10^2|3.7e-05|1.6e-05|0.00115|4e-05|4.1e-05|4e-05|3.9e-05|9.2e-05|1e-05|
|10^3|0.000325|0.00015|0.010474|0.000395|0.000422|0.000391|4.7e-05|0.000188|8.9e-05|
|10^4|0.004011|0.002185|0.117871|0.004128|0.003968|0.003914|3.7e-05|0.001117|0.00073|
|10^5|0.056653|0.036201|1.28979|0.043841|0.047062|0.045696|3.1e-05|0.018395|0.007436|
|10^6|1.14899|1.02883|14.8436|0.480792|0.479679|0.47861|7e-05|0.291747|0.071457|
|10^7|18.3514|17.9365|175.28|5.21174|5.75037|5.26387|5e-05|4.24086|0.740487|
|10^8|281.794|280.843|1844.73|55.3695|55.1324|55.0423|4.3e-05|55.8803|7.17556|
|10^9|4981.37|4980.49|5727.56|972.242|972.115|972.007|5.7e-05|973.196|74.3658|

