#include "bstree.hpp"

using namespace BSTree;
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    Tree<int> tree; //наше дерево
    for (int i = 1; i < argc; i++)
        tree.insert(atoi(argv[i]));
    
    for(;;) { //меню
        cout << "\tВЫБЕРИТЕ ОПЕРАЦИЮ:\n1. Вывести дерево на экран\n2. Вывести список узлов дерева\n3. Добавить узел в дерево\n4. Удалить узел из дерева\n5. Сохранить дерево в файл\n6. Загрузить дерево из файла\n7. Проверить наличие узла\n8. Завершить работу программы" << endl;
        int ch;
        bool exit_ = false;
        cin >> ch;
        while (!cin) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Ошибка. Повторите ввод: ";
            cin >> ch;
        }
        switch (ch) {
            case 1: { //вывод дерева
                if (tree.empty()) {
                    cout << "Дерево пусто" << endl;
                    break;
                }
                tree.print_tree();
            } break;
            case 2: {
                if (tree.empty()) {
                    cout << "Дерево пусто" << endl;
                    break;
                }
                cout << "\tа. Прямой обход\n\tb. Поперечный обход\n\tc. Обратный обход\n";
                char way;
                cin >> way;
                switch(way) {
                    case 'a': {
                        tree.print(cout, BSTree::direct);
                        cout << endl;
                    } break;
                    case 'b': {
                        tree.print(cout, BSTree::symmetric);
                        cout << endl;
                    } break;
                    case 'c': {
                        tree.print(cout, BSTree::reverse);
                        cout << endl;
                    } break;
                    default: cout << "Введено некорректное значение\n";
                        break;
                }
            } break;
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
                suc = tree.insert(val);
                if (suc) {
                    cout << "УСПЕХ" << endl;
                }
                else
                    cout << "Узел уже существует в дереве" << endl;
            } break;
            case 4: {
                if (tree.empty()) {
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
                if (!tree.exists(value)) {
                    cout << "Узел не найден\n";
                    break;
                }
                bool ready = false;
                ready = tree.remove(value);
                if(ready)
                    cout << "Элемент успешно удален" << endl;
                else
                    cout << "Элемент не был удален" << endl;
            } break;
            case 5: {
                cout << "Введите название файла: ";
                string path;
                cin >> path;
                bool b;
                b = tree.save(path);
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
                b = tree.load(path);
                if (b) {
                    cout << "Дерево успешно полученно\n";
                }
                else
                    cout << "Дерево не было полученно\n";
            } break;
            case 7: {
                if (tree.empty()) {
                    cout << "Дерево пусто" << endl;
                    break;
                }
                cout << "Введите значение для поиска: ";
                int search;
                cin >> search;
                if (tree.exists(search))
                    cout << "Узел найден\n";
                else
                    cout << "Узел не найден\n";
            } break;
            case 8: { //выходим или не выходим по 'Да'/'Нет', иначе 'ОШИБКА'
                string cExit;
                cout << "Вы уверены, что хотите выйти из программы? (Да|Нет)\n";
                cin >> cExit;
                if (cExit == "Да") {
                    cout << "До свидания!\n";
                    exit_ = true;
                }
                else if (cExit == "Нет")
                    break;
                else
                    cout << "Введено некорректное значение\n";
            } break;
            default: cout << "Такой операции нет\n"; break;
        }
        if (exit_)
            break;
    }
}
