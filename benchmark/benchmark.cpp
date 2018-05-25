#include <iostream>
#include <locale>
#include <ctime>
#include <cmath>
#include "bstree.hpp"

int main(){
    std::ofstream out("answer.txt");
    out<<"y";
    out.close();
    clock_t  start;
    clock_t  end;
    BSTree::Tree<int> tree;
    std::freopen("tree_bench.txt", "w", stdout);
    std::freopen("answer.txt", "r", stdin);
    std::ofstream fout("bench.txt");
    for (unsigned int i = 1; i <= 9; i++){
        fout << "Adding" << std::endl;
        start = clock();
        for (unsigned int j = 1; j <= pow(10,i); j++)
            tree.insert(rand());
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout << "Existing" << std::endl;
        start = clock();
        for (unsigned int j = 1; j <= pow(10,i); j++)
            tree.exists(rand());
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout << "Print: " << std::endl;
        start = clock();
        tree.print_tree();
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout << "Direct print:" << std::endl;
        start = clock();
        tree.print(std::cout, BSTree::direct);
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout << "Symmetric print:" << std::endl;
        start = clock();
        tree.print(std::cout, BSTree::symmetric);
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout << "Reverse print:" << std::endl;
        start = clock();
        tree.print(std::cout, BSTree::reverse);
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        fout<<"Saving:"<<std::endl;
        start = clock();
        tree.save("BSTree.txt");
        end = clock() - start;
        fout<<"e"<< i <<" : "<<(float)end/CLOCKS_PER_SEC<<std::endl;
        
        fout<<"Loading:"<<std::endl;
        start = clock();
        tree.load("BSTree.txt");
        end = clock() - start;
        fout<<"e"<< i <<" : "<<(float)end/CLOCKS_PER_SEC<<std::endl;
        
        fout << "Removing" << std::endl;
        start = clock();
        for (unsigned int j = 1; j <= pow(10,i); j++)
            tree.remove(rand());
        end = clock() - start;
        fout << "e" << i << ": " << (float)end/CLOCKS_PER_SEC << std::endl;
        
        tree.~Tree();
    }
}
