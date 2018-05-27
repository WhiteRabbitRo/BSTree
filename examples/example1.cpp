#include <iostream>
#include "bstree.hpp"
int main() {
    BSTree::Tree<int> tree{5, 3, 9, 7, 2, 1, 4, 8, 6, 10};
    std::cout << "The example of tree: " << tree << std::endl;
    std::cout << "The example of direct print of nodes using iterator: ";
    BSTree::BSTI<int> it1 = tree.begin();
    while(it1 != tree.end()) {
        std::cout << *it1 << " ";
        ++it1;
    }
        
    std::cout << *it1 << "\n";
    
    std::cout << "The example of reverse print of node using iterator: ";
    BSTree::BSTI<int> it2 = tree.rbegin();
    for(; it2 != tree.rend(); ++it2) {
        BSTree::BSTI<int> ex = it2;
        std::cout << *ex << " ";
    }
    std::cout << *it2 << "\n";

}
