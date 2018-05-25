#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstring>
#include <initializer_list>

namespace BSTree
{
// ===============
// Наш узел дерева
// ===============

template <typename T>
struct Node {
    T data;
    Node<T>* left; //ветка влево
    Node<T>* right; //ветка вправо
    Node(T val) : data{val}, left{nullptr}, right{nullptr} {}; //конструтор
};

enum traversal_order { direct, symmetric, reverse}; //для обходов

// ===========
// Наше дерево
// ===========

template <typename T>
class Tree {
public:
    Tree() : root{nullptr} {}; //конструктор
    Tree (std::initializer_list<T>); // Лист инициализации
    auto swap(Tree<T>&) -> void; //поменять значения
    Tree(const Tree<T>&); //конструктор копирования
    void print_tree(); //вывод дерева
    bool empty(); //проверка дерева на пустоту
    bool exists(T); //поиск узла
    bool insert(T); //добавление узла
    bool remove(T); //удаление узла
    bool save(const std::string&); //запись дерева в файл
    bool load(const std::string&); //загрузка дерева из файла
    auto print(std::ostream& stream, traversal_order ord) const -> std::ostream&; //вывод узлов тремя способами
    template <typename T1>
    auto friend operator<<(std::ostream& stream, const Tree<T1>& tree) -> std::ostream& { //оператор вывода в поток
        tree.print(stream, direct);
        return stream;
    };
    template <typename T2>
    auto operator=(const Tree<T2>& tree) -> Tree<T2>& {  //оператор присваивания
        Tree tr(tree);
        this->clean(root);
        this->swap(tr);
        return *this;
    };
    ~Tree() { //деструктор
        clean(root);
        this->root = nullptr;
    };
private:
    Node<T>* root;
    void clean(Node<T>*); //для удаления
};

// ============================
// Реализация методов и функций
// ============================

template <typename T>
void Tree<T>::clean(Node<T>* node) { //отчистка дерева
    if (node != nullptr){
    clean(node->left);
    clean(node->right);
    delete node;
}
    node = nullptr;
}

template <typename T>
Tree<T>::Tree(std::initializer_list<T> list) : Tree() { //лист инициализации
    this->clean(root);
    for (auto x: list)
        this->insert(x);
}

template <typename T>
auto Tree<T>::swap(Tree<T>& tree) -> void { //поменять адреса деревьев
    std::swap(this->root, tree.root);
}

template <typename T>
Tree<T>::Tree(const Tree<T>& tree) { //конструктор копирования
    this->clean(root);
    std::string str;
    std::stringstream out(str);
    out << tree;
    T value;
    while(out) {
        out >> value;
        this->insert(value);
    }
}

template <typename T>
void right_sym_print(Node<T>* branch, int space) { //симметричный правый обход для функции вывода дерева
    if (branch == nullptr)
        return;
    right_sym_print(branch->right, space=space+2);
    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << "--" << branch->data << std::endl;
    right_sym_print(branch->left, space=space+2);
}

template <typename T>
void Tree<T>::print_tree() { //вывод дерева
    right_sym_print(this->root->right, 0);
    std::cout << this->root->data << std::endl;
    right_sym_print(this->root->left, 0);
}

template <typename T>
bool Tree<T>::empty() { //проверка на пустоту дерева
    if (this->root == nullptr)
        return true;
    else
        return false;
}

template <typename T>
bool Tree<T>::exists(T val) { //поиск узла
    if (root == nullptr)
        return false;
    Node<T>* find = root;
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

template <typename T>
bool Tree<T>::insert(T val) { //добавление узла
    if(exists(val))
        return false;
    if (root == nullptr) {
        root = new Node<T> {val};
        return true;
    }
    Node<T>* add = root;
    while (add != nullptr) {
        if (val < add->data) {
            if (add->left == nullptr) {
                add->left = new Node<T> {val};
                return true;
            }
            add = add->left;
        }
        else {
            if (add->right == nullptr) {
                add->right = new Node<T> {val};
                return true;
            }
            add = add->right;
        }
    }
    return false;
}

template <typename T>
bool Tree<T>::remove (T val) { //удаление узла
    if (!this->exists(val))
        return false;
    Node<T>* add = root;
    Node<T>* parrent = nullptr;
    while (add->data != val) {
        parrent = add;
        if(val < add->data)
            add = add -> left;
        else
            add = add -> right;
    }
    Node<T>* removed = nullptr;
    if ((add->left==nullptr) || (add->right==nullptr)) {
        removed = add;
        Node<T>* child = nullptr;
        if(add -> left != nullptr )
            child = add ->left;
        if(add -> right != nullptr)
            child = add -> right;
        if (parrent == nullptr) {
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
        Node<T>* mleft = add->right;
        Node<T>* befmleft = add;
        while (mleft->left != nullptr) { //ищем самое крайнее левое (минимальное)
            befmleft = mleft;
            mleft = mleft->left;
        }
        add->data = mleft->data;
        removed = mleft;
        if (befmleft ->left == mleft) {
            befmleft -> left = nullptr;
        }
        else
            befmleft->right= mleft->right;
    }
    delete removed;
    removed = nullptr;
    return true;
}

template <typename T>
bool Tree<T>::save(const std::string& path) { //запись дерева в файл
    struct stat buffer;
    if (stat(path.c_str(), &buffer) == 0) {
        std::string nAns;
        std::cout << "Перезаписать файл? (y/n)" << std::endl;
        std::cin >> nAns;
        if ((nAns == "y") || (nAns == "Y") || (nAns == "yes") || (nAns == "Yes") || (nAns == "YES")) {
            std::ofstream fout(path, std::ios_base::trunc);
            fout << *this;
            fout.close();
        }
        else
            return false;
    }
    else {
        std::ofstream fout(path, std::ios_base::trunc);
        fout << *this;
        fout.close();
    }
    return true;
}

template <typename T>
bool Tree<T>::load(const std::string& path) { //загрузка дерева из файла
    std::ifstream fin(path.c_str());
    if (!fin.is_open())
        return false;
    this->clean(root);
    this->root = nullptr;
    T value;
    fin >> value;
    if(!fin)
        return false;
    while(fin) {
        this->insert(value);
        fin >> value;
    }
    return true;
}

template <typename T>
auto direct_print(std::ostream& stream, Node<T>* node) -> std::ostream& { //прямой вывод узлов дерева
    if (node != nullptr) {
        stream << node->data << " ";
        direct_print(stream, node->left);
        direct_print(stream, node->right);
    }
    return stream;
}


template <typename T>
auto symmetric_print(std::ostream& stream, Node<T>* node) -> std::ostream& { //симметричный вывод узлов дерева
    if (node != nullptr) {
        symmetric_print(stream, node->left);
        stream << node->data << " ";
        symmetric_print(stream, node->right);
    }
    return stream;
}

template <typename T>
auto reverse_print(std::ostream& stream, Node<T>* node) -> std::ostream& { //обратный вывод узлов дерева
    if (node != nullptr) {
        reverse_print(stream, node->left);
        reverse_print(stream, node->right);
        stream << node->data << " ";
    }
    return stream;
}

template <typename T>
auto Tree<T>::print(std::ostream& stream, traversal_order ord) const -> std::ostream& { //вывод узлов тремя способами
    switch (ord) {
    case direct:
        direct_print(stream, root);
        break;
    case symmetric:
        symmetric_print(stream, root);
        break;
    case reverse:
        reverse_print(stream, root);
        break;
    }
    return stream;
}
}
