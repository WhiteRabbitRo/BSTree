#include <iterator>

namespace BSTree{
    
    /*!
     \brief Struct for the BSTree, tree node
     */
    template <typename T>
    struct Node {
        T data;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        Node(T val) : data{val}, left{nullptr}, right{nullptr}, parent{nullptr} {}; ///конструтор
    };
    
    /*!
     \brief Iterator class for the BSTree
     */
    template<typename T>
    class BSTI : public std::iterator<std::bidirectional_iterator_tag, Node<T>> {
    private:
        Node<T>* ptr;
        Node<T>* next(Node<T>*);
        Node<T>* prev(Node<T>*);
        auto min_el(Node<T>* )const -> Node<T>*;
        auto max_el(Node<T>* )const -> Node<T>*;
    public:
        /// Constructors
        BSTI() : ptr{nullptr} {};
        BSTI(Node<T>* ptr) : ptr{ptr} {};
        BSTI(const BSTI& other) : ptr{other.ptr} {};
        
        ///Operators
        auto operator=(const BSTI<T>& it)->BSTI<T>& {
            ptr = it.ptr;
        }
        auto operator++()->BSTI<T>& {
            ptr = next(ptr);
            return *this;
        }
        auto operator++(int val)->BSTI<T> {
            for (unsigned int i = 0; i < val; i++)
                ++(*this);
            return *this;
        }
        auto operator--()->BSTI<T>& {
            ptr = prev(ptr);
            return *this;
        }
        auto operator--(int val)->BSTI<T> {
            for (unsigned int i = 0; i < val; i++)
                --(*this);
            return *this;
        }
        auto operator*() const ->T& {
            return ptr->data;
        }
        template<typename T1>
        auto  operator==(const BSTI<T1>& other) const -> bool{
            if(this->ptr == other.ptr)
                return true;
            return false;
        }
        template<typename T2>
        auto   operator!=(const BSTI<T2>& other) const -> bool{
            if(ptr != other.ptr)
                return true;
            return false;
        }
        template<typename T3>
        auto friend swap(BSTI<T3>& it1, BSTI<T3>& it2) -> void{
            std::swap(it1.ptr, it2.ptr);
        }
    };
    /*!
     \brief The next modulo value
     */
    template<typename T>
    auto BSTI<T>::next(Node<T>* node)->Node<T>* {
        if(node->right != nullptr)
            return min_el(node->right);
            Node<T>* parent_ = node->parent;
            while(parent_ != nullptr && node == parent_ ->right){
                node = parent_;
                parent_= parent_->parent;
            }
        return parent_;
    }
    /*!
     \brief The previous modulo value
     */
    template<typename T>
    auto BSTI<T>::prev(Node<T>* node)->Node<T>* {
        if(node->left != nullptr)
            return max_el(node->left);
            Node<T>* parent_ = node->parent;
            while(parent_ != nullptr && node == parent_ ->left){
                node = parent_;
                parent_= parent_->parent;
            }
        return parent_;
    }
    /*!
     \brief Minimal element
     */
    template<typename T>
    auto BSTI<T>::min_el(Node<T>* node )const -> Node<T>*{
        if(node->left == nullptr)
            return node;
        while(node->left != nullptr)
            node = node ->left;
            return node;
    }
    /*!
     \brief Maximal element
     */
    template<typename T>
    auto BSTI<T>::max_el(Node<T>* node )const -> Node<T>*{
        if(node->right == nullptr)
            return node;
        while(node->right != nullptr)
            node = node ->right;
            return node;
    }
}
