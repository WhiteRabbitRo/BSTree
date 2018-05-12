#include "bstree.cpp"
using namespace BSTree;
int main(){
    // Пример работы программы
    Tree tree1; //пустое дерево
    Tree tree2 = {5,1,3,6,8,4}; //инициализация листом
    cout << tree1 << tree2 << endl; //вывод дерева (оператор <<)
    tree2.print_tree(); //вывод дерева графически
    tree1 = tree2; //оператор присваивания
    tree1.print(direct); //прямой вывод дерева
    cout << "\n";
    Tree tree3;
    tree3.insert(10); //функция добавления узла
    tree3.insert(1);
    tree3.insert(6);
    tree3.print(symmetric); //симметричный вывод узлов
    cout << "\n";
    
    cout << boolalpha << tree2.exists(10) << "\n"; //функция поиска узла
    cout << tree3.exists(1) << "\n";
    
    tree2.remove(4); //функция удаления элемента
    cout << tree2 << "\n";
    
    tree3.save("text.txt"); //функция записи дерева в файл
    tree1.load("text.txt"); //функция загрузки дерева из файла
    cout << tree1;
}
