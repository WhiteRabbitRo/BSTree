#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <initializer_list>
#include <iterator.hpp>

namespace BSTree
{
///For order
enum traversal_order { direct, symmetric, reverse};
/*!
 \brief Main class Binary Search Tree
 */
template <typename T>
class Tree {
public:
    ///Constructors
    Tree() : root{nullptr} {};
    Tree (std::initializer_list<T>);
    auto swap(Tree<T>&) -> void;
    Tree(const Tree<T>&);
    
    void print_tree(); ///Tree printing
    bool empty(); ///Empty checking
    bool exists(T); ///Existing of the node
    bool insert(T); ///Adding new node
    bool remove(T); ///Removing of node
    bool save(const std::string&); ///Download into the file
    bool load(const std::string&); ///Download from the file
    auto print(std::ostream& stream, traversal_order ord) const -> std::ostream&; ///Three way printing
    
    auto begin() -> BSTI<T>{
        Node<T>* node = root;
        while(node->left!=nullptr)
            node = node->left;
        BSTI<T> it (node);
        return it;
    }
    auto end() -> BSTI<T>{
        Node<T>* node = root;
        while(node->right!=nullptr)
            node = node->right;
        BSTI<T> it (node);
        return it;
    }
    auto rbegin() -> BSTI<T> {
        Node<T>* node = root;
        while(node->right!=nullptr)
            node = node->right;
        BSTI<T> it (node);
        return it;
    }
    auto rend() -> BSTI<T> {
        Node<T>* node = root;
        while(node->left!=nullptr)
            node = node->left;
        BSTI<T> it (node);
        return it;
    }
    
    ///Operators
    template <typename T1>
    auto friend operator<<(std::ostream& stream, const Tree<T1>& tree) -> std::ostream& {
        tree.print(stream, direct);
        return stream;
    };
    template <typename T2>
    auto operator=(const Tree<T2>& tree) -> Tree<T2>& {
        Tree tr(tree);
        this->clean(root);
        this->swap(tr);
        return *this;
    };
    
    ~Tree() { ///Destructor
        clean(root);
        this->root = nullptr;
    };
private:
    Node<T>* root;
    void clean(Node<T>*);
};
    /*!
     \brief Function for cleaning tree
     */
template <typename T>
void Tree<T>::clean(Node<T>* node) {
    if (node != nullptr){
        clean(node->left);
        clean(node->right);
        delete node;
    }
    node = nullptr;
}
    /*!
     \brief Initialization list
     */
template <typename T>
Tree<T>::Tree(std::initializer_list<T> list) : Tree() {
    this->clean(root);
    for (auto x: list)
        this->insert(x);
}
    /*!
     \brief Swaping of addresses
     */
template <typename T>
auto Tree<T>::swap(Tree<T>& tree) -> void {
    std::swap(this->root, tree.root);
}
    /*!
     \brief Copy constructor
     */
template <typename T>
Tree<T>::Tree(const Tree<T>& tree) {
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
    /*!
     \brief Symmetric right way(for the tree print)
     */
template <typename T>
void right_sym_print(Node<T>* branch, int space) {
    if (branch == nullptr)
        return;
    right_sym_print(branch->right, space=space+2);
    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << "--" << branch->data << std::endl;
    right_sym_print(branch->left, space=space+2);
}
    /*!
     \brief Tree print
     */
template <typename T>
void Tree<T>::print_tree() {
    right_sym_print(this->root->right, 0);
    std::cout << this->root->data << std::endl;
    right_sym_print(this->root->left, 0);
}
    /*!
     \brief Empty check
     */
template <typename T>
bool Tree<T>::empty() {
    if (this->root == nullptr)
        return true;
    else
        return false;
}
    /*!
     \brief Exist node
     */
template <typename T>
bool Tree<T>::exists(T val) {
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
    /*!
     \brief Node adding
     */
template <typename T>
bool Tree<T>::insert(T val) {
    if(exists(val))
        return false;
    if (root == nullptr) {
        root = new Node<T> {val};
        root -> parent = nullptr;
        return true;
    }
    Node<T>* add = root;
    while (add != nullptr) {
        if (val < add->data) {
            if (add->left == nullptr) {
                add->left = new Node<T> {val};
                add->left->parent = add;
                return true;
            }
            add = add->left;
        }
        else {
            if (add->right == nullptr) {
                add->right = new Node<T> {val};
                add->right->parent = add;
                return true;
            }
            add = add->right;
        }
    }
    return false;
}
    /*!
     \brief Node removing
     */
template <typename T>
bool Tree<T>::remove (T val) {
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
            if(child != nullptr)
                child -> parent = parrent;
        }
    }
    if ((add->left!=nullptr) && (add->right!=nullptr)) {
        Node<T>* mleft = add->right;
        Node<T>* befmleft = add;
        while (mleft->left != nullptr) {
            befmleft = mleft;
            mleft = mleft->left;
        }
        add->data = mleft->data;
        removed = mleft;
        if (befmleft ->left == mleft) {
            befmleft -> left = nullptr;
        }
        else
            mleft->parent->right= mleft->right;
    }
    delete removed;
    removed = nullptr;
    return true;
}
    /*!
     \brief In-file-load
     */
template <typename T>
bool Tree<T>::save(const std::string& path) {
    std::ifstream fin(path.c_str());
    if (!fin.is_open()) {
        std::ofstream fout(path.c_str());
        fout << *this;
        fout.close();
        return true;
    }
    else {
        std::string sAns;
        std::cout << "Перезаписать файл? (y/n)" << std::endl;
        std::cin >> sAns;
        if ((sAns == "y") || (sAns == "Y") || (sAns == "yes") || (sAns == "Yes") || (sAns == "YES")) {
            std::ofstream fout(path.c_str());
            fout << *this;
            fout.close();
            return true;
        }
        else
            return false;
    }
}
    /*!
     \brief Out-file-load
     */
template <typename T>
bool Tree<T>::load(const std::string& path) {
    std::ifstream fin(path.c_str());
    if (!fin.is_open())
        return false;
    this->~Tree();
    T value;
    fin >> value;
    if(!fin) {
        return false;
        fin.close();
    }
    while(fin) {
        this->insert(value);
        fin >> value;
    }
    fin.close();
    return true;
}
    /*!
     \brief Direct print
     */
template <typename T>
auto direct_print(std::ostream& stream, Node<T>* node) -> std::ostream& {
    if (node != nullptr) {
        stream << node->data << " ";
        direct_print(stream, node->left);
        direct_print(stream, node->right);
    }
    return stream;
}
        /*!
         \brief Symmetric print
         */
template <typename T>
auto symmetric_print(std::ostream& stream, Node<T>* node) -> std::ostream& {
    if (node != nullptr) {
        symmetric_print(stream, node->left);
        stream << node->data << " ";
        symmetric_print(stream, node->right);
    }
    return stream;
}
        /*!
         \brief Reverse print
         */
template <typename T>
auto reverse_print(std::ostream& stream, Node<T>* node) -> std::ostream& {
    if (node != nullptr) {
        reverse_print(stream, node->left);
        reverse_print(stream, node->right);
        stream << node->data << " ";
    }
    return stream;
}
        /*!
         \brief Print-in-three-ways
         */
    template <typename T>
    auto Tree<T>::print(std::ostream& stream, traversal_order ord) const -> std::ostream& {
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
