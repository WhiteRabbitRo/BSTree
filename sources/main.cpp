#include "bstree.cpp"

using namespace BSTree;
void menu(Tree*, bool); //меню
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    Tree tree; //наше дерево
    for (unsigned int i = 1; i < argc; i++)
        tree.insert(atoi(argv[i]));
    
    menu(&tree, tree.empty_check());
}
