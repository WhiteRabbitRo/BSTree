#include "bstree.cpp"

using namespace BSTree;
void menu(Tree*, bool);  //меню
int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "Rus");
  bool empty = true;  //для пустого дерева

  Tree tree;  //наше дерево

  bool suc = false;  //проверка успешности добавления элементов в дерево
  if (argc > 1) {
    for (unsigned int i = 1; i < argc; i++) suc = tree.insert(atoi(argv[i]));
    if (suc)
      cout << "ДЕРЕВО УСПЕШНО СФОРМИРОВАНО" << endl;
    else
      cout << "ПОВТОРЯЮЩИЕСЯ ЭЛЕМЕНТЫ УДАЛЕНЫ" << endl;
    empty = false;
  } else
    empty = true;

  menu(&tree, empty);
}
