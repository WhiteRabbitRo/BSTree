#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <initializer_list>
#include "bstree.hpp"
using namespace std;
void BSTree::Tree::clean(Node*& node) {
    //обратный обход для удаления
    if (node == nullptr)
        return;
    clean(node->left);
    clean(node->right);
    delete node;
    node = nullptr;
}
bool BSTree::Tree::exists(int val) {
    //поиск узла
    if (root == nullptr)
        return false;
    Node* find = root;
    while (find->data != val) {
        if(val < find->data)
            find = find -> left;
        else
            find = find -> right;
        if(find == nullptr)
            return false;
    }
    return true;
}
bool BSTree::Tree::insert(int val){
    //добавление узла
    if(exists(val))
        return false;
    if (root == nullptr) {
        root = new Node{
            val
        }
        ;
        return true;
    }
    Node* add = root;
    while (add != nullptr) {
        if (val < add->data) {
            if (add->left == nullptr) {
                add->left = new Node{
                    val
                }
                ;
                return true;
            }
            add = add->left;
        }
        else {
            if (add->right == nullptr) {
                add->right = new Node{
                    val
                }
                ;
                return true;
            }
            add = add->right;
        }
    }
    return false;
}
auto BSTree::swap(Tree& tree, Node* curr) -> void {
    //поменять значения
    if (curr == nullptr)
        return;
    tree.insert(curr->data);
    swap(tree, curr->left);
    swap(tree, curr->right);
}
BSTree::Tree::Tree(const Tree& tree){
    //конструктор копирования
    swap(*this, tree.root);
}
auto BSTree::Tree::operator=(const Tree& tree) -> Tree& {
    //оператор присваивания
    this->clean(root);
    swap(*this, tree.root);
    return *this;
}
;
BSTree::Tree::Tree(std::initializer_list<int> list) {
    //лист инициализации
    this->clean(root);
    for (auto x: list)
        this->insert(x);
}
void right_sym_print(BSTree::Node* branch, int space) {
    //симметричный правый обход для функции вывода дерева
    if (branch == nullptr)
        return;
    right_sym_print(branch->right, space=space+2);
    for (int i = 0;
         i < space;
         i++)
        cout << " ";
    cout << "--" << branch->data << endl;
    right_sym_print(branch->left, space=space+2);
}
void BSTree::Tree::print_tree() {
    //вывод дерева
    right_sym_print(root->right, 0);
    cout << root->data << endl;
    right_sym_print(root->left, 0);
}
void direct_print(BSTree::Node* node){
    //прямой вывод узлов дерева
    if (node == nullptr) {
        return;
    }
    cout << node->data << " ";
    direct_print(node->left);
    direct_print(node->right);
}
void symmetric_print(BSTree::Node* node){
    //симметричный вывод узлов дерева
    if (node == nullptr) {
        return;
    }
    symmetric_print(node->left);
    cout << node->data << " ";
    symmetric_print(node->right);
}
void reverse_print(BSTree::Node* node){
    //обратный вывод узлов дерева
    if (node == nullptr) {
        return;
    }
    reverse_print(node->left);
    reverse_print(node->right);
    cout << node->data << " ";
}
void BSTree::Tree::print(traversal_order ord) {
    //вывод узлов тремя способами
    switch (ord) {
        case direct: direct_print(root);
            break;
        case symmetric: symmetric_print(root);
            break;
        case reverse: reverse_print(root);
            break;
    }
}
        bool BSTree::Tree::remove (int val){
            //удаление узла
            Node* add = root;
            Node* parrent = nullptr;
            while (add->data != val) {
                parrent = add;
                if(val < add->data)
                    add = add -> left;
                else
                    add = add -> right;
            }
            Node* removed = nullptr;
            if ((add->left==nullptr) || (add->right==nullptr)) {
                removed = add;
                Node* child = nullptr;
                if(add -> left != nullptr )
                    child = add ->left;
                if(add -> right != nullptr)
                    child = add -> right;
                if (parrent == nullptr){
                    root = child;
                }
                else {
                    if (add->data > parrent->data)
                        parrent->right = child;
                    if (add->data < parrent->data)
                        parrent->left = child;
                }
            }
            if ((add->left!=nullptr) && (add->right!=nullptr)) {
                Node* mleft = add->right;
                Node* befmleft = add;
                while (mleft->left != nullptr) {
                    //ищем самое крайнее левое (минимальное)
                    befmleft = mleft;
                    mleft = mleft->left;
                }
                add->data = mleft->data;
                removed = mleft;
                if (befmleft ->left == mleft){
                    befmleft -> left = nullptr;
                }
                else
                    befmleft->right= mleft->right;
            }
            delete removed;
            removed = nullptr;
            return true;
        }
        bool BSTree::Tree::save(const std::string& path){
            //запись дерева в файл
            struct stat buffer;
            if (stat(path.c_str(), &buffer) == 0) {
                string nAns;
                cout << "Перезаписать файл? (y/n)" << endl;
                cin >> nAns;
                if ((nAns == "y") || (nAns == "Y") || (nAns == "yes") || (nAns == "Yes") || (nAns == "YES")) {
                    ofstream fout(path, ios_base::trunc);
                    fout << *this;
                    fout.close();
                }
                else
                    return false;
            }
            else {
                ofstream fout(path, ios_base::trunc);
                fout << *this;
                fout.close();
            }
            return true;
        }
        bool BSTree::Tree::load(const std::string& path) {
            //загрузка дерева из файла
            std::ifstream fin(path.c_str());
            if (!fin.is_open())
                return false;
            this->clean(root);
            int value;
            fin >> value;
            if(!fin)
                return false;
            while(fin){
                this->insert(value);
                fin >> value;
            }
            return true;
        }
        bool BSTree::Tree::empty_check(){
            if (this->root == nullptr)
                return true;
            else
                return false;
        }
        void menu(BSTree::Tree* tree, bool empty){
            //меню
            cout << "\tВЫБЕРИТЕ ОПЕРАЦИЮ:\n1. Вывести дерево на экран\n2. Вывести список узлов дерева\n3. Добавить узел в дерево\n4. Удалить узел из дерева\n5. Сохранить дерево в файл\n6. Загрузить дерево из файла\n7. Проверить наличие узла\n8. Завершить работу программы" << endl;
            int ch;
            cin >> ch;
            while (!cin) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Ошибка. Повторите ввод: ";
                cin >> ch;
            }
            switch (ch) {
                case 1: {
                    //вывод дерева
                    if (empty) {
                        cout << "Дерево пусто" << endl;
                        break;
                    }  
                    tree->print_tree();
                }
                    break;
                case 2: {
                    if (empty) {
                        cout << "Дерево пусто" << endl;
                        break;
                    }
                    cout << "\tа. Прямой обход\n\tb. Поперечный обход\n\tc. Обратный обход\n";
                    char way;
                    cin >> way;
                    switch(way) {
                        case 'a': tree->print(BSTree::direct);
                            break;
                        case 'b': tree->print(BSTree::symmetric);
                            break;
                        case 'c': tree->print(BSTree::reverse);
                            break;
                        default: cout << "Введено некорректное значение";
                            break;
                    }
                    cout << endl;
                }
                    break;
                case 3: {
                    cout << "Введите значение для нового узла: ";
                    int val;
                    cin >> val;
                    while (!cin) {
                        cin.clear();
                        while (cin.get() != '\n');
                        cout << "Ошибка. Повторите ввод: ";
                        cin >> val;
                    }
                    bool suc = false;
                    suc = tree->insert(val);
                    if (suc) {
                        cout << "УСПЕХ" << endl;
                        empty = false;
                    }
                    else
                        cout << "Узел уже существует в дереве" << endl;
                }
                    break;
                case 4: {
                    if (empty) {
                        cout << "Дерево пусто" << endl;
                        break;
                    }
                    int value;
                    cout << "Введите удаляемый элемент: ";
                    cin >> value;
                    while (!cin) {
                        cin.clear();
                        while (cin.get() != '\n');
                        cout << "Ошибка. Повторите ввод: ";
                        cin >> value;
                    }
                    if (!tree->exists(value)) {
                        cout << "Узел не найден\n";
                        break;
                    }
                    bool ready = false;
                    ready = tree->remove(value);
                    if(ready)
                        cout << "Элемент успешно удален" << endl;
                    else
                        cout << "Элемент не был удален" << endl;
                    if (tree->empty_check())
                        empty = true;
                }
                    break;
                case 5: {
                    cout << "Введите название файла: ";
                    string path;
                    cin >> path;
                    bool b;
                    b = tree->save(path);
                    if (b)
                        cout << "Дерево успешно записано в файл\n";
                    else
                        cout << "Дерево не было записано в файл\n";
                }
                    break;
                case 6: {
                    cout << "Введите название файла: ";
                    string path;
                    cin >> path;
                    bool b;
                    b = tree->load(path);
                    if (b) {
                        cout << "Дерево успешно полученно\n";
                        empty = false;
                    }
                    else
                        cout << "Дерево не было полученно\n";
                }
                    break;
                case 7: {
                    if (empty) {
                        cout << "Дерево пусто" << endl;
                        break;
                    }
                    cout << "Введите значение для поиска: ";
                    int search;
                    cin >> search;
                    if (tree->exists(search))
                        cout << "Узел найден\n";
                    else
                        cout << "Узел не найден\n";
                }
                    break;
                case 8: {
                    //выходим или не выходим по 'Да'/'Нет', иначе 'ОШИБКА'
                    string cExit;
                    cout << "Вы уверены, что хотите выйти из программы? (Да|Нет)\n";
                    cin >> cExit;
                    if (cExit == "Да") {
                        cout << "До свидания!\n";
                        return;
                    }
                    else if (cExit == "Нет")
                        break;
                    else
                        cout << "Введено некорректное значение\n";
                }
                    break;
                default: cout << "Такой операции нет\n";
                    break;
            }
            menu(tree, empty);
        }
