#include "catch.hpp"
#include "bstree.hpp"

using namespace BSTree;

TEST_CASE("CREATING TREE") {
    Tree<int> tree;
    REQUIRE(tree.empty() == true);
    Tree<int> tree_{1};
    REQUIRE(tree_.empty() == false);
}

TEST_CASE("TRAVERSAL ORDER PRINT") {
    Tree<int> tree = { 10, 4, 3, 9, 15, 6, 12, 1, 11, 8, 2, 14, 7, 5, 13};
    std::string dir = "10 4 3 1 2 9 6 5 8 7 15 12 11 14 13 ";
    std::string sym = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 ";
    std::string rev = "2 1 3 5 7 8 6 9 4 11 13 14 12 15 10 ";
    
    std::string str;
    std::stringstream out(str);
    
    tree.print(out, direct);
    out<<std::endl;
    tree.print(out, symmetric);
    out<<std::endl;
    tree.print(out, reverse);
    out<<std::endl;
    
    std::string result_dir;
    std::string result_sym;
    std::string result_rev;
    
    getline(out, result_dir);
    getline(out, result_sym);
    getline(out, result_rev);
    
    REQUIRE(dir == result_dir);
    REQUIRE(sym == result_sym);
    REQUIRE(rev == result_rev);
}

TEST_CASE("ADDING NODE") {
    Tree<int> tree = { 51, 93, 71, 16, 4, 53, 11, 32};
    
    tree.insert(80);
    tree.insert(25);
    tree.insert(1);
    
    std::string str;
    std::stringstream out(str);
    
    tree.print(out, direct);
    
    std::string result = "51 16 4 1 11 32 25 93 71 53 80 ";
    std::string result_of_adding;
    getline(out, result_of_adding);
    
    REQUIRE(result == result_of_adding);
}

TEST_CASE("DELETING NODE") {
    Tree<int> tree = { 25, 34, 12, 4, 7, 67, 78, 9, 0 };
    
    tree.remove(25);
    tree.remove(0);
    tree.remove(12);
    
    std::string result = "34  4  7  9  67  78  ";
    
    std::string str;
    std::stringstream out(str);
    
    tree.print(out, direct);
    
    std::string result_of_deleting;
    getline(out, result_of_deleting);
    
    REQUIRE(result == result_of_deleting);
}

TEST_CASE("INPUT IN FILE") {
    Tree<int> tree = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    
    std::string text = "8  4  2  1  3  6  5  7  12  10  9  11  14  13  15  ";
    std::string buffer;
    std::stringstream out (buffer);
    
    out << tree;
    
    std::string result;
    getline(out, result);
    
    REQUIRE(result == text);
}

TEST_CASE("EXISTENCE OF NODE") {
    Tree<int> tree = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    REQUIRE(tree.exists(8) == true);
    REQUIRE(tree.exists(100) == false);
}

TEST_CASE("SAVE AND LOAD"){
    Tree<int> tree = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    Tree<int> tree1;
    
    std::ofstream fout("answer.txt");
    fout << "y";
    fout.close();
    
    std::freopen("answer.txt", "r", stdin);
    
    tree.save("BStree.txt");
    tree1.load("BStree.txt");
    
    std::string text = "8  4  2  1  3  6  5  7  12  10  9  11  14  13  15  ";
    std::string buffer;
    std::stringstream out (buffer);
    
    out << tree1;
    
    std::string result;
    getline(out, result);
    
    REQUIRE(result == text);
}
