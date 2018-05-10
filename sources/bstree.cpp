#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "bstree.hpp"

using namespace std;

void BSTree::Tree::clean(Node*& node) {  //обратный обход для удаления
  if (node == nullptr) return;
  clean(node->left);
  clean(node->right);
  delete node;
  node = nullptr;
}

bool BSTree::Tree::exists(int val) {  //поиск узла
  if (root == nullptr) return false;
  Node* find = root;
  while (find->data != val) {
    if (val < find->data)
      find = find->left;
    else
      find = find->right;
    if (find == nullptr) return false;
  }
  return true;
}

bool BSTree::Tree::insert(int val) {  //добавление узла
  if (exists(val)) return false;
  if (root == nullptr) {
    root = new Node{val};
    return true;
  }
  Node* add = root;
  while (add != nullptr) {
    if (val < add->data) {
      if (add->left == nullptr) {
        add->left = new Node{val};
        return true;
      }
      add = add->left;
    } else {
      if (add->right == nullptr) {
        add->right = new Node{val};
        return true;
      }
      add = add->right;
    }
  }
  return false;
}

BSTree::Tree::Tree(std::initializer_list<int> list) {  //лист инициализации
  Tree new_tree;
  this->clean(root);
  this->root = new_tree.root;
  bool b;
  for (auto x : list) {
    b = this->insert(x);
  }
}

void right_sym_print(
    BSTree::Node* branch,
    int space) {  //симметричный правый обход для функции вывода дерева
  if (branch == nullptr) return;
  right_sym_print(branch->right, space = space + 2);
  for (unsigned int i = 0; i < space; i++) cout << " ";
  cout << "--" << branch->data << endl;
  right_sym_print(branch->left, space = space + 2);
}

void BSTree::Tree::print_tree() {  //вывод дерева
  right_sym_print(root->right, 0);
  cout << root->data << endl;
  right_sym_print(root->left, 0);
}

void direct_print(BSTree::Node* node) {  //прямой вывод узлов дерева
  if (node == nullptr) {
    return;
  }
  cout << node->data << " ";
  direct_print(node->left);
  direct_print(node->right);
}

void symmetric_print(BSTree::Node* node) {  //симметричный вывод узлов дерева
  if (node == nullptr) {
    return;
  }
  symmetric_print(node->left);
  cout << node->data << " ";
  symmetric_print(node->right);
}

void reverse_print(BSTree::Node* node) {  //обратный вывод узлов дерева
  if (node == nullptr) {
    return;
  }
  reverse_print(node->left);
  reverse_print(node->right);
  cout << node->data << " ";
}

void BSTree::Tree::print(traversal_order ord) {  //вывод узлов тремя способами
  switch (ord) {
    case direct:
      direct_print(root);
      break;
    case symmetric:
      symmetric_print(root);
      break;
    case reverse:
      reverse_print(root);
      break;
  }
}

auto print_oper(std::ostream& stream, const BSTree::Node* node)
    -> std::ostream & {  //прямой обход для оператора <<
  if (node != nullptr) {
    stream << node->data << " ";
    print_oper(stream, node->left);
    print_oper(stream, node->right);
  }
  return stream;
}

auto BSTree::operator<<(std::ostream& stream, const Tree& tree)
    -> std::ostream & {  //оператор вывода в поток
  Node* out_ = tree.root;
  if (out_ == nullptr) {
    stream << "Дерево пусто\n";
    return stream;
  }
  return print_oper(stream, tree.root);
}

auto BSTree::Tree::operator=(const Tree& tree) -> Tree & {
  this->clean(root);
  this->root = tree.root;
  return *this;
}

bool BSTree::Tree::remove(int val) {  //удаление узла
  Node* add = root;
  Node* before = nullptr;
  while (add->data != val) {
    before = add;
    if (val < add->data)
      add = add->left;
    else
      add = add->right;
  }
  if (add == nullptr) return false;

  Node* removed = nullptr;
  if ((add->left == nullptr) && (add->right == nullptr)) {
    if (add->data > before->data) before->right = nullptr;
    if (add->data < before->data) before->left = nullptr;
  }
  if ((add->left == nullptr) && (add->right != nullptr)) {
    if (add->data > before->data) before->right = add->right;
    if (add->data < before->data) before->left = add->right;
  }
  if ((add->left != nullptr) && (add->right == nullptr)) {
    if (add->data > before->data) before->right = add->left;
    if (add->data < before->data) before->left = add->left;
  }
  if ((add->left != nullptr) && (add->right != nullptr)) {
    Node* del = add->right;
    Node* bef = add;
    while (del->left != nullptr) {  //ищем самое крайнее левое (минимальное)
      bef = del;
      del = del->left;
    }
    if (add->data > before->data) {
      before->right = del;
      del->left = add->left;
      bef->left = nullptr;
    }
    if (add->data < before->data) {
      before->left = del;
      del->left = add->left;
      bef->left = nullptr;
    }
  }
  removed = add;
  delete removed;
  add = nullptr;
  return true;
}

bool BSTree::Tree::save(const std::string& path) {  //запись дерева в файл
  struct stat buffer;
  if (stat(path.c_str(), &buffer) == 0) {
    string nAns;
    cout << "Перезаписать файл? (y/n)" << endl;
    cin >> nAns;
    if ((nAns == "y") || (nAns == "Y") || (nAns == "yes") || (nAns == "Yes") ||
        (nAns == "YES")) {
      ofstream fout(path, ios_base::trunc);
      fout << *this;
      fout.close();
    } else
      return false;
  } else {
    ofstream fout(path, ios_base::trunc);
    fout << *this;
    fout.close();
  }
  return true;
}
bool BSTree::Tree::load(const std::string& path) {  //загрузка дерева из файла
  bool b;
  std::ifstream fin(path.c_str());
  if (!fin.is_open()) return false;
  this->clean(root);
  int value;
  fin >> value;
  if (!fin) return false;
  while (fin) {
    this->insert(value);
    fin >> value;
  }
  return true;
}

void menu(BSTree::Tree* tree, bool empty) {  //меню
  cout << "\tВЫБЕРИТЕ ОПЕРАЦИЮ:\n1. Вывести дерево на экран\n2. Вывести список "
          "узлов дерева\n3. Добавить узел в дерево\n4. Удалить узел из "
          "дерева\n5. Сохранить дерево в файл\n6. Загрузить дерево из "
          "файла\n7. Проверить наличие узла\n8. Завершить работу программы"
       << endl;

  int ch;
  cin >> ch;
  switch (ch) {
    case 1: {  //вывод дерева
      if (empty) {
        cout << "Дерево пусто" << endl;
        break;
      }
      tree->print_tree();
    } break;
    case 2: {
      if (empty) {
        cout << "Дерево пусто" << endl;
        break;
      }

      cout << "\tа. Прямой обход\n\tb. Поперечный обход\n\tc. Обратный обход\n";
      char way;
      cin >> way;

      switch (way) {
        case 'a':
          tree->print(BSTree::direct);
          break;
        case 'b':
          tree->print(BSTree::symmetric);
          break;
        case 'c':
          tree->print(BSTree::reverse);
          break;
        default:
          cout << "Введено некорректное значение";
          break;
      }
      cout << endl;
    } break;
    case 3: {
      cout << "Введите значение для нового узла: ";
      int val;
      cin >> val;
      while (!cin) {
        cin.clear();
        while (cin.get() != '\n')
          ;
        cout << "Ошибка. Повторите ввод: ";
        cin >> val;
      }
      bool suc = false;
      suc = tree->insert(val);
      if (suc) {
        cout << "УСПЕХ" << endl;
        empty = false;
      } else
        cout << "Узел уже существует в дереве" << endl;
    } break;
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
        while (cin.get() != '\n')
          ;
        cout << "Ошибка. Повторите ввод: ";
        cin >> value;
      }

      if (!tree->exists(value)) {
        cout << "Узел не найден\n";
        break;
      }

      bool ready = false;
      ready = tree->remove(value);

      if (ready)
        cout << "Элемент успешно удален" << endl;
      else
        cout << "Элемент не был удален" << endl;
    } break;
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
    } break;
    case 6: {
      cout << "Введите название файла: ";
      string path;
      cin >> path;
      bool b;
      b = tree->load(path);
      if (b) {
        cout << "Дерево успешно получено\n";
        empty = false;
      } else
        cout << "Дерево не было получено\n";
    } break;
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
    } break;
    case 8: {  //выходим или не выходим по 'Да'/'Нет', иначе 'ОШИБКА'
      string cExit;
      cout << "Вы уверены, что хотите выйти из программы? (Да|Нет)\n";
      cin >> cExit;

      if (cExit == "Да") {
        cout << "До свидания!\n";
        return;
      } else if (cExit == "Нет")
        break;
      else
        cout << "Введено некорректное значение\n";
    } break;
  }
  menu(tree, empty);
}
