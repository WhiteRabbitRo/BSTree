namespace BSTree
{
    struct Node {
        int data;
        Node* left; //ветка влево
        Node* right; //ветка вправо
        Node(int val) : data{val}, left{nullptr}, right{nullptr} {}; //конструтор
    };
}
namespace BSTree
{
    enum traversal_order { direct, symmetric, reverse};
    class Tree { //класс дерево
    public:
        Tree() : root{nullptr} {}; //конструктор
        Tree (std::initializer_list<int> list); // Лист инициализации
        Tree(const Tree& tree); //конструктор копирования
        void print_tree(); //вывод дерева
        bool exists(int val); //поиск узла
        bool insert(int val); //добавление узла
        bool remove(int val); //удаление узла
        bool save(const std::string& path); //запись дерева в файл
        bool load(const std::string& path); //загрузка дерева из файла
        void print(traversal_order ord); //вывод узлов тремя способами
        auto friend operator<<(std::ostream& stream, const Tree&) -> std::ostream&; //оператор вывода в поток
        auto operator=(const Tree& tree) -> Tree&;  //оператор присваивания
        ~Tree() { //деструктор
            clean(root);
        };
    private:
        Node* root;
        void clean(Node*& node); //для удаления
    };
}



